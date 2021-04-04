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

		[DllImport("Bindings.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern bool SaveController(Controller.Marshalled controller);

		[DllImport("Bindings.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern UInt32 GetControllerLimit();

		public const int CONTROLLER_LIMIT = 128;
	}
}
