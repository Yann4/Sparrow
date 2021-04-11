using InputEditor.Bindings;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace InputEditor.InputBindings
{
	class AssetManager
	{
		AssetManager()
		{
			Debug.Assert(CONTROLLER_LIMIT == GetControllerLimit(), "C#/C++ mismatch, update one to match the other");
		}

		public class ControllerSet
		{
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
			public Controller.Marshalled[] Controllers = new Controller.Marshalled[32];
		}

		[DllImport("Bindings.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern bool SaveController(Controller.Marshalled controller);
		
		[DllImport("Bindings.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern Controller.Marshalled GetController(Int32 index);
		
		[DllImport("Bindings.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern Int32 GetControllerCount();

		[DllImport("Bindings.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern UInt32 GetControllerLimit();
		
		[DllImport("Bindings.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern void LoadAllControllers();

		public const int CONTROLLER_LIMIT = 64;
	}
}
