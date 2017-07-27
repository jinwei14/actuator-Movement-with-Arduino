//#include <conio.h>
//#include <iostream>
//
//using namespace System;
//using namespace std;
//using namespace Spiricon::Automation;
//
//public ref class Runner
//{
//private:
//	// Declare BeamGage Automation client
//	AutomatedBeamGage^ bga;
//	Array ^frameData;
//
//public:
//	Runner()
//	{
//		// Start BeamGage Automation client
//		bga = gcnew AutomatedBeamGage("ClientOne", true);
//	}
//
//	void Run()
//	{
//		cout << "Press any key to exit." << endl << endl;
//
//		cout << "Ultracalling.... ";
//		// Invoke an ultracal cycle
//		bga->Calibration->Ultracal();
//		cout << "finished" << endl << endl;
//
//		// Create and register for the new frame event
//		newFrame ^ cb = gcnew newFrame(this, &Runner::NewFrameFunction);
//		AutomationFrameEvents events((IAFrame ^)bga->ResultsPriorityFrame);
//		events.OnNewFrame += cb;
//
//		_getch();
//
//		// Shutdown BeamGage
//		delete[] frameData;
//		bga->Instance->Shutdown();
//	}
//
//private:
//	void NewFrameFunction()
//	{
//		//Obtain the frame data and use it
//		frameData = bga->ResultsPriorityFrame->DoubleData;
//
//		// Print the ID and Total counts of the frame
//		printf("Frame # %i, Total: %.2f, FrameData(%i,0): %.5f \r",
//			(int)bga->FrameInfoResults->ID, bga->PowerEnergyResults->Total, (int)bga->FrameInfoResults->Height, (double)frameData->GetValue(0));
//	}
//};
//
//int main(cli::array<System::String ^> ^args)
//{
//	Runner runMe;
//	runMe.Run();
//	return 0;
//}