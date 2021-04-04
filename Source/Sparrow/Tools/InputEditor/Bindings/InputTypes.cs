using InputEditor.InputBindings;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;

namespace InputEditor.Bindings
{

	class Controller
	{
		public string Name;
		public List<ControllerElement> Elements = new List<ControllerElement>();
		public ControllerMap Map = new ControllerMap();

		public Marshalled AsMarshalled()
		{
			return new Marshalled(this);
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct Marshalled
		{
			public Marshalled(Controller controller)
			{
				Debug.Assert(controller.Elements.Count() <= AssetManager.CONTROLLER_LIMIT, "Arbitrary limit breached! Bump number");
				Debug.Assert(controller.Map.Count() <= AssetManager.CONTROLLER_LIMIT, "Arbitrary limit breached! Bump number");

				Name = controller.Name;

				ElementCount = (UInt32)controller.Elements.Count();
				Elements = new ControllerElement.Marshalled[AssetManager.CONTROLLER_LIMIT];
				Array.Copy(controller.Elements.Select(element => element.AsMarshalled()).ToArray(), Elements, ElementCount);

				ActionElementCount = controller.Map.Count();

				MapActions = new UInt32[AssetManager.CONTROLLER_LIMIT];
				Array.Copy(controller.Map.Actions(), MapActions, ActionElementCount);

				MapElements = new UInt32[AssetManager.CONTROLLER_LIMIT];
				Array.Copy(controller.Map.Elements(), MapElements, ActionElementCount);
			}

			[MarshalAs(UnmanagedType.LPStr)]
			public string Name;

			public UInt32 ElementCount;
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = AssetManager.CONTROLLER_LIMIT)]
			public ControllerElement.Marshalled[] Elements;

			public UInt32 ActionElementCount;
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = AssetManager.CONTROLLER_LIMIT)]
			public UInt32[] MapActions;
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = AssetManager.CONTROLLER_LIMIT)]
			public UInt32[] MapElements;
		}
	}

	class ControllerElement
	{
		public UInt32 ElementID = 0;
		public float ActivationThreshold = 0.0f;
		public string Name = string.Empty;

		public Marshalled AsMarshalled()
		{
			return new Marshalled(this);
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct Marshalled
		{
			public UInt32 ElementID;
			public float ActivationThreshold;
			[MarshalAs(UnmanagedType.LPStr)]
			public string Name;

			public Marshalled(ControllerElement element)
			{
				ElementID = element.ElementID;
				ActivationThreshold = element.ActivationThreshold;
				Name = element.Name;
			}
		}
	}

	class ControllerMap
	{
		public Dictionary<UInt32, ControllerElement> Map = new Dictionary<uint, ControllerElement>();

		public UInt32 Count() { return (UInt32)Map.Count; }
		public UInt32[] Actions() { return Map.Keys.ToArray(); }
		public UInt32[] Elements() { return Map.Values.Select(element => element.ElementID).ToArray(); }
	}
}
