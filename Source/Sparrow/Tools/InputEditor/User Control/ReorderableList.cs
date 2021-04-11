using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

/// <typeparam name="IT">The item type to be stored in this list</typeparam>
internal class ReorderableList<IT> where IT : class
{
	private readonly SolidColorBrush m_alternator1, m_alternator2; // Background colours for the list items to alternate between
	private readonly ListBox m_ListBox; // The target ListBox we're modifying
	private readonly string m_displayMemberPath; // The name of the member in to display 
	private readonly IList<IT> m_items = new ObservableCollection<IT>();
	private Point m_cursorStartPos;
	private Action m_OnReorder;

	public IEnumerable Items { get { return m_items; } }

	/// <summary>
	/// Initializes the list (this must be done after components are initialized and loaded!).
	/// </summary>
	/// <param name="resourceProvider">Pass 'this' for this parameter</param>
	/// <param name="listBox">The target ListBox control to modify</param>
	/// <param name="displayMemberPath">The name of the member in the generic type contained in this list, to be displayed</param>
	public ReorderableList(ListBox listBox, Action onReorder, SolidColorBrush alternator1 = null, SolidColorBrush alternator2 = null, string displayMemberPath = "")
	{
		m_ListBox = listBox;
		m_displayMemberPath = displayMemberPath;
		m_alternator1 = alternator1;
		m_alternator2 = alternator2;
		m_OnReorder = onReorder;

		Initialize();
	}

	private void Initialize()
	{
		// Set the list box's items source and tell it what member in the IT class to use for the display name
		// Add an event handler for preview mouse move

		if (!string.IsNullOrEmpty(m_displayMemberPath))
		{
			m_ListBox.DisplayMemberPath = m_displayMemberPath;
		}
		m_ListBox.ItemsSource = m_items;
		m_ListBox.PreviewMouseMove += OnListPreviewMouseMove;

		// Create the item container style to be used by the listbox
		// Add mouse event handlers to the style

		Style style = new Style(typeof(ListBoxItem));
		style.Setters.Add(new Setter(UIElement.AllowDropProperty, true));
		style.Setters.Add(new EventSetter(UIElement.PreviewMouseLeftButtonDownEvent, new MouseButtonEventHandler(OnListPreviewMouseLeftButtonDown)));
		style.Setters.Add(new EventSetter(UIElement.DropEvent, new DragEventHandler(OnListDrop)));

		// Add triggers to alternate the background colour of each element based on its alternation index
		// (Remove this, as well as the two SolidColorBrush resources if you don't want this feature)
		if (m_alternator1 != null && m_alternator2 != null)
		{
			Trigger trigger1 = new Trigger()
			{
				Property = ItemsControl.AlternationIndexProperty,
				Value = 0
			};

			Setter setter1 = new Setter()
			{
				Property = Control.BackgroundProperty,
				Value = m_alternator1
			};

			trigger1.Setters.Add(setter1);
			style.Triggers.Add(trigger1);

			Trigger trigger2 = new Trigger()
			{
				Property = ItemsControl.AlternationIndexProperty,
				Value = 1
			};

			Setter setter2 = new Setter()
			{
				Property = Control.BackgroundProperty,
				Value = m_alternator2
			};

			trigger2.Setters.Add(setter2);
			style.Triggers.Add(trigger2);
		}

		// Set the item container style

		m_ListBox.ItemContainerStyle = style;
	}

	/// <summary>
	/// Adds an item to the list. If [ignoreDuplicates] is false and the item is already in the list,
	/// the item won't be added.
	/// </summary>
	/// <param name="item">The item to add</param>
	/// <param name="ignoreDuplicates">Whether or not to add the item regardless of whether it's already in the list</param>
	/// <returns>Whether or not the item was added</returns>
	public bool Add(IT item, bool ignoreDuplicates = true)
	{
		if (!ignoreDuplicates && Contains(item)) return false;

		m_items.Add(item);
		return true;
	}

	/// <summary>
	/// Clears all items from list
	/// </summary>
	public void Clear()
	{
		m_items.Clear();
	}

	/// <summary>
	/// Removes an item from the list.
	/// </summary>
	/// <param name="item">The item to remove</param>
	/// <returns>Whether or not the item was removed from the list. This will be false if the item was not in the list to begin with.</returns>
	public bool Remove(IT item)
	{
		if (Contains(item)) return false;

		m_items.Remove(item);
		return true;
	}

	public bool RemoveSelected(Action<IT> OnRemove)
	{
		if(m_ListBox.SelectedItem == null)
		{
			return false;
		}

		IT selected = m_ListBox.SelectedItem as IT;
		if (OnRemove != null)
		{
			OnRemove(selected);
		}

		m_items.Remove(selected);
		return true;
	}

	/// <summary>
	/// Returns whether or not the list contains the given item.
	/// </summary>
	/// <param name="item">The item to check for</param>
	/// <returns>Whether or not the list contains the given item.</returns>
	public bool Contains(IT item)
	{
		return m_items.Contains(item);
	}

	private void OnListPreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
	{
		m_cursorStartPos = e.GetPosition(null);
	}

	private void OnListPreviewMouseMove(object sender, MouseEventArgs e)
	{
		Point currentCursorPos = e.GetPosition(null);
		Vector cursorVector = m_cursorStartPos - currentCursorPos;

		if (e.RightButton == MouseButtonState.Pressed
			&& (Math.Abs(cursorVector.X) > SystemParameters.MinimumHorizontalDragDistance
			|| Math.Abs(cursorVector.Y) > SystemParameters.MinimumVerticalDragDistance))
		{
			ListBoxItem targetItem = FindVisualParent<ListBoxItem>(((DependencyObject)e.OriginalSource));
			if (targetItem != null)
			{
				DragDrop.DoDragDrop(targetItem, targetItem.DataContext, DragDropEffects.Move);
			}
		}
	}

	private void OnListDrop(object sender, DragEventArgs e)
	{
		if (sender is ListBoxItem item)
		{
			IT source = e.Data.GetData(typeof(IT)) as IT;
			IT target = item.DataContext as IT;

			int sourceIndex = m_ListBox.Items.IndexOf(source);
			int targetIndex = m_ListBox.Items.IndexOf(target);

			Move(source, sourceIndex, targetIndex);
		}
	}

	private void Move(IT source, int sourceIndex, int targetIndex)
	{
		if (sourceIndex < targetIndex)
		{
			m_items.Insert(targetIndex + 1, source);
			m_items.RemoveAt(sourceIndex);
		}
		else
		{
			int removeIndex = sourceIndex + 1;
			if (m_items.Count + 1 > removeIndex)
			{
				m_items.Insert(targetIndex, source);
				m_items.RemoveAt(removeIndex);
			}
		}

		if (m_OnReorder != null)
		{
			m_OnReorder();
		}
	}

	private T FindVisualParent<T>(DependencyObject child) where T : DependencyObject
	{
		DependencyObject parentObject = VisualTreeHelper.GetParent(child);
		if (parentObject == null) return null;
		if (parentObject is T parent) return parent;

		return FindVisualParent<T>(parentObject);
	}
}