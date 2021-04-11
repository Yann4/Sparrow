using InputEditor.Bindings;
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;

namespace InputEditor.User_Control
{
	/// <summary>
	/// Interaction logic for ControllerElement_UC.xaml
	/// </summary>
	public partial class ControllerElement_UC : UserControl
	{
		public ControllerElement Element;

		public ControllerElement_UC(ControllerElement element)
		{
			Element = element;
			Debug.Assert(Element != null);

			InitializeComponent();
			RefreshUI();
		}

		private void RefreshUI()
		{
			if (ElementNameBox != null)
			{
				ElementNameBox.SetValue(TextBox.TextProperty, Element.Name);
			}

			if (ActivationThresholdSlider != null)
			{
				ActivationThresholdSlider.SetValue(Slider.ValueProperty, (double)Element.ActivationThreshold);
			}

			if (SliderLabel != null)
			{
				SliderLabel.SetValue(Label.ContentProperty, string.Format("Activation Threshold: {0:F1}", ActivationThresholdSlider.Value));
			}
		}

		private void ActivationThreshold_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
		{
			if (this.IsLoaded)
			{
				Element.ActivationThreshold = (float)Math.Round(e.NewValue, 1);
				RefreshUI();
			}
		}

		private void ElementNameBox_TextChanged(object sender, TextChangedEventArgs e)
		{
			if (this.IsLoaded)
			{
				Element.Name = ElementNameBox.Text;
				RefreshUI();
			}
		}
	}
}
