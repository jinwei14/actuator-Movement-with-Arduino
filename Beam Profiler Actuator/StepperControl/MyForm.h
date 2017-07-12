#pragma once
#include <string>
#using <System.dll>

namespace StepperControl {

	
	using namespace System;

	//io port
	using namespace System::IO::Ports;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>

	public ref class MyForm : public System::Windows::Forms::Form
	{

	public:
		//display string in the display text field
		String^ displayStr = "";
		MyForm(void)
		{

			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			cli::array<String^>^ serialPorts = nullptr;
			try {
				// Get a list of serial port names.
				serialPorts = SerialPort::GetPortNames();
			}
			catch (Win32Exception^ ex) {
				Console::WriteLine(ex->Message);
			}

			//Console::WriteLine("The following serial ports were found:");
			for each(String^ port in serialPorts) {
				this->comboBox1->Items->Add(port);
			}

	

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  poartLabel;
	protected:

	private: System::Windows::Forms::Label^  distanceLabel;


	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  moveButton;
	private: System::Windows::Forms::Label^  displayLabel;
    


	private: System::Windows::Forms::Button^  comfirmButton;

	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  LaserFireButton;
	private: System::Windows::Forms::Button^  CheckImageButton;
	private: System::Windows::Forms::Button^  stopButton;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->poartLabel = (gcnew System::Windows::Forms::Label());
			this->distanceLabel = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->moveButton = (gcnew System::Windows::Forms::Button());
			this->displayLabel = (gcnew System::Windows::Forms::Label());
			this->comfirmButton = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->LaserFireButton = (gcnew System::Windows::Forms::Button());
			this->CheckImageButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// poartLabel
			// 
			this->poartLabel->AutoSize = true;
			this->poartLabel->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->poartLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->poartLabel->Location = System::Drawing::Point(12, 66);
			this->poartLabel->Name = L"poartLabel";
			this->poartLabel->Size = System::Drawing::Size(179, 27);
			this->poartLabel->TabIndex = 0;
			this->poartLabel->Text = L"Port (COMX):";
			this->poartLabel->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// distanceLabel
			// 
			this->distanceLabel->AutoSize = true;
			this->distanceLabel->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->distanceLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->distanceLabel->Location = System::Drawing::Point(12, 197);
			this->distanceLabel->Name = L"distanceLabel";
			this->distanceLabel->Size = System::Drawing::Size(206, 27);
			this->distanceLabel->TabIndex = 1;
			this->distanceLabel->Text = L"Distance (step):";
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->Location = System::Drawing::Point(299, 201);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(283, 28);
			this->textBox2->TabIndex = 3;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			// 
			// moveButton
			// 
			this->moveButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->moveButton->AutoSize = true;
			this->moveButton->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->moveButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->moveButton->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->moveButton->Location = System::Drawing::Point(452, 260);
			this->moveButton->Name = L"moveButton";
			this->moveButton->Size = System::Drawing::Size(130, 42);
			this->moveButton->TabIndex = 5;
			this->moveButton->Text = L"Move";
			this->moveButton->UseVisualStyleBackColor = false;
			this->moveButton->Click += gcnew System::EventHandler(this, &MyForm::moveButton_Click);
			// 
			// displayLabel
			// 
			this->displayLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->displayLabel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->displayLabel->Location = System::Drawing::Point(12, 573);
			this->displayLabel->Name = L"displayLabel";
			this->displayLabel->Size = System::Drawing::Size(570, 304);
			this->displayLabel->TabIndex = 6;
			this->displayLabel->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// comfirmButton
			// 
			this->comfirmButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->comfirmButton->AutoSize = true;
			this->comfirmButton->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->comfirmButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comfirmButton->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comfirmButton->Location = System::Drawing::Point(452, 119);
			this->comfirmButton->Name = L"comfirmButton";
			this->comfirmButton->Size = System::Drawing::Size(130, 43);
			this->comfirmButton->TabIndex = 7;
			this->comfirmButton->Text = L"Confirm";
			this->comfirmButton->UseVisualStyleBackColor = false;
			this->comfirmButton->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
			// 
			// comboBox1
			// 
			this->comboBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(299, 66);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(283, 26);
			this->comboBox1->TabIndex = 8;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// LaserFireButton
			// 
			this->LaserFireButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->LaserFireButton->AutoSize = true;
			this->LaserFireButton->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->LaserFireButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->LaserFireButton->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LaserFireButton->Location = System::Drawing::Point(12, 528);
			this->LaserFireButton->Name = L"LaserFireButton";
			this->LaserFireButton->Size = System::Drawing::Size(130, 42);
			this->LaserFireButton->TabIndex = 9;
			this->LaserFireButton->Text = L"Fire Laser";
			this->LaserFireButton->UseVisualStyleBackColor = false;
			this->LaserFireButton->Click += gcnew System::EventHandler(this, &MyForm::LaserFire_Click);
			// 
			// CheckImageButton
			// 
			this->CheckImageButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->CheckImageButton->AutoSize = true;
			this->CheckImageButton->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->CheckImageButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->CheckImageButton->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CheckImageButton->Location = System::Drawing::Point(223, 528);
			this->CheckImageButton->Name = L"CheckImageButton";
			this->CheckImageButton->Size = System::Drawing::Size(147, 42);
			this->CheckImageButton->TabIndex = 10;
			this->CheckImageButton->Text = L"Check Image";
			this->CheckImageButton->UseVisualStyleBackColor = false;
			this->CheckImageButton->Click += gcnew System::EventHandler(this, &MyForm::CheckImageButton_Click);
			// 
			// stopButton
			// 
			this->stopButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->stopButton->AutoSize = true;
			this->stopButton->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->stopButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->stopButton->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->stopButton->Location = System::Drawing::Point(435, 528);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(147, 42);
			this->stopButton->TabIndex = 11;
			this->stopButton->Text = L"halt Moving";
			this->stopButton->UseVisualStyleBackColor = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(594, 886);
			this->Controls->Add(this->stopButton);
			this->Controls->Add(this->CheckImageButton);
			this->Controls->Add(this->LaserFireButton);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->comfirmButton);
			this->Controls->Add(this->displayLabel);
			this->Controls->Add(this->moveButton);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->distanceLabel);
			this->Controls->Add(this->poartLabel);
			this->MinimumSize = System::Drawing::Size(616, 874);
			this->Name = L"MyForm";
			this->Text = L"linear actuator Controller";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		//declear as global variable;
		int baudRate = 115200;
		gcroot<SerialPort^> uStepper;
		//////////////////
		bool flag = true;
		gcroot<String^> portName; //Defines the COM Port used to communicate with the uStepper 
		portName = gcnew String(comboBox1->Text);
		if (comboBox1->Text == "") {
		    displayStr = displayStr + "\nPort should not be empty";
			displayLabel->Text = displayStr;
			flag = false;
		}
		if (flag) {
			//Creates uStepper object and opens the connection
			uStepper = gcnew SerialPort(portName, baudRate);
			uStepper->Open();
			displayStr = displayStr + "\nConnect successfully";
			displayLabel->Text = displayStr;
		}
	}
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

}

private: System::Void LaserFire_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void CheckImageButton_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void moveButton_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}