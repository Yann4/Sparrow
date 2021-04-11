using InputEditor.Bindings;
using InputEditor.InputBindings;
using InputEditor.User_Control;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace InputEditor
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		private int m_SelectedController = -1;
		private Controller CurrentController { get { if (m_SelectedController == -1) { return null; } return m_LoadedControllers[m_SelectedController]; } }

		private List<Controller> m_LoadedControllers = new List<Controller>();

		private ReorderableList<ControllerElement_UC> ReorderableElements;

		public MainWindow()
		{
			InitializeComponent();

			AssetManager.LoadAllControllers();
			Controller.Marshalled[] marshalledControllers = new Controller.Marshalled[AssetManager.GetControllerCount()];
			for(int idx = 0; idx < marshalledControllers.Length; idx++)
			{
				marshalledControllers[idx] = AssetManager.GetController(idx);
			}

			foreach (Controller.Marshalled marshalled in marshalledControllers)
			{
				m_LoadedControllers.Add(new Controller(marshalled));
				comboBox.Items.Add(marshalled.Name);
			}

			ReorderableElements = new ReorderableList<ControllerElement_UC>(Elements, OnReorderElements);

			SelectController(0);
		}

		private void OnReorderElements()
		{
			uint idx = 0;
			foreach(ControllerElement_UC controllerElement in ReorderableElements.Items)
			{
				controllerElement.Element.ElementID = idx;
				idx++;
			}

			CurrentController.Elements.Sort((a, b) => a.ElementID.CompareTo(b.ElementID));
		}

		private void NewController_Click(object sender, RoutedEventArgs e)
		{
			Controller controller = new Controller("New Controller");
			m_LoadedControllers.Add(controller);

			comboBox.Items.Add(controller.Name);
			SelectController(m_LoadedControllers.Count - 1);
		}

		private void textBox_TextChanged(object sender, TextChangedEventArgs e)
		{
			if(sender is ComboBox)
			{
				return;
			}


			if (CurrentController != null)
			{
				CurrentController.Name = textBox.Text;

				int idx = comboBox.SelectedIndex;
				comboBox.Items[idx] = CurrentController.Name;
				comboBox.SelectedIndex = idx;
			}
		}

		private void Save_Click(object sender, RoutedEventArgs e)
		{
			if (CurrentController != null)
			{
				AssetManager.SaveController(CurrentController.AsMarshalled());
			}
		}

		private void SelectController(int idx)
		{
			m_SelectedController = idx;

			comboBox.SelectedIndex = m_SelectedController;
			PopulateElements();
			textBox.SetValue(TextBox.TextProperty, m_LoadedControllers[idx].Name);
		}

		private void PopulateElements()
		{
			ReorderableElements.Clear();
			foreach (ControllerElement element in CurrentController.Elements)
			{
				User_Control.ControllerElement_UC uiElement = new User_Control.ControllerElement_UC(element);
				ReorderableElements.Add(uiElement);
			}
		}

		private void AddElement_Click(object sender, RoutedEventArgs e)
		{
			ControllerElement element = new ControllerElement();
			CurrentController.Elements.Add(element);
			ReorderableElements.Add(new ControllerElement_UC(element));
		}

		private void RemoveElement_Click(object sender, RoutedEventArgs e)
		{
			ReorderableElements.RemoveSelected((ControllerElement_UC element) => CurrentController.Elements.Remove(element.Element));
		}

		private void comboBox_DropDownClosed(object sender, EventArgs e)
		{
			if (m_SelectedController != comboBox.SelectedIndex)
			{
				SelectController(comboBox.SelectedIndex);
			}
		}
	}
}
