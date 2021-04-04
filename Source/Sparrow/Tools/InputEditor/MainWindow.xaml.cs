using InputEditor.Bindings;
using InputEditor.InputBindings;
using System;
using System.Collections.Generic;
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
		private Controller m_CurrentController;

		public MainWindow()
		{
			InitializeComponent();
		}

		private void NewController_Click(object sender, RoutedEventArgs e)
		{
			m_CurrentController = new Controller();
			m_CurrentController.Name = textBox.Text;
			m_CurrentController.Elements.Add(new ControllerElement());
			m_CurrentController.Elements.Add(new ControllerElement());
			m_CurrentController.Elements.Add(new ControllerElement());
			m_CurrentController.Elements.Add(new ControllerElement());
			m_CurrentController.Map.Map.Add(1, m_CurrentController.Elements[0]);
			m_CurrentController.Map.Map.Add(2, m_CurrentController.Elements[1]);
			m_CurrentController.Map.Map.Add(3, m_CurrentController.Elements[2]);
			m_CurrentController.Map.Map.Add(5, m_CurrentController.Elements[3]);
		}

		private void textBox_TextChanged(object sender, TextChangedEventArgs e)
		{
			if(m_CurrentController != null)
			{
				m_CurrentController.Name = textBox.Text;
			}
		}

		private void Save_Click(object sender, RoutedEventArgs e)
		{
			if(m_CurrentController != null)
			{
				AssetManager.SaveController(m_CurrentController.AsMarshalled());
			}
		}
	}
}
