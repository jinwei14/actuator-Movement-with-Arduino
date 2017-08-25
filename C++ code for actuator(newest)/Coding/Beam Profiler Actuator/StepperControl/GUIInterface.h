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
	/// Summary for GUIInterface
	/// </summary>
	public ref class GUIInterface : public System::Windows::Forms::Form
	{
	public:
		//display string in the display text field
		//String^ displayStr = "";
		GUIInterface(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
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
		~GUIInterface()
		{
			if (components)
			{
				delete components;
				
			}
			exit(0);
		}

	private: System::Windows::Forms::Label^  poartLabel;
	protected:
	private: System::Windows::Forms::Label^  distanceLabel;
	private: System::Windows::Forms::TextBox^  movementTextBox2;
	private: System::Windows::Forms::Button^  moveButton;

	private: System::Windows::Forms::Button^  confirmButton;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  haltButton;
	private: System::Windows::Forms::Button^  setHomeButton;
	private: System::Windows::Forms::Button^  calculateButton;
	private: System::Windows::Forms::TextBox^  displayBox;




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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(GUIInterface::typeid));
			this->poartLabel = (gcnew System::Windows::Forms::Label());
			this->distanceLabel = (gcnew System::Windows::Forms::Label());
			this->movementTextBox2 = (gcnew System::Windows::Forms::TextBox());
			this->moveButton = (gcnew System::Windows::Forms::Button());
			this->confirmButton = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->haltButton = (gcnew System::Windows::Forms::Button());
			this->setHomeButton = (gcnew System::Windows::Forms::Button());
			this->calculateButton = (gcnew System::Windows::Forms::Button());
			this->displayBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// poartLabel
			// 
			this->poartLabel->AutoSize = true;
			this->poartLabel->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->poartLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->poartLabel->Location = System::Drawing::Point(12, 67);
			this->poartLabel->Name = L"poartLabel";
			this->poartLabel->Size = System::Drawing::Size(179, 27);
			this->poartLabel->TabIndex = 0;
			this->poartLabel->Text = L"Port (COMX):";
			// 
			// distanceLabel
			// 
			this->distanceLabel->AutoSize = true;
			this->distanceLabel->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->distanceLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->distanceLabel->Location = System::Drawing::Point(12, 235);
			this->distanceLabel->Name = L"distanceLabel";
			this->distanceLabel->Size = System::Drawing::Size(206, 27);
			this->distanceLabel->TabIndex = 1;
			this->distanceLabel->Text = L"Distance (step):";
			// 
			// movementTextBox2
			// 
			this->movementTextBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->movementTextBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->movementTextBox2->Location = System::Drawing::Point(299, 234);
			this->movementTextBox2->Name = L"movementTextBox2";
			this->movementTextBox2->Size = System::Drawing::Size(283, 28);
			this->movementTextBox2->TabIndex = 2;
			this->movementTextBox2->Text = L"Enter=50mm";
			this->movementTextBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// moveButton
			// 
			this->moveButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->moveButton->AutoSize = true;
			this->moveButton->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->moveButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->moveButton->Enabled = false;
			this->moveButton->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->moveButton->Location = System::Drawing::Point(435, 280);
			this->moveButton->Name = L"moveButton";
			this->moveButton->Size = System::Drawing::Size(147, 42);
			this->moveButton->TabIndex = 3;
			this->moveButton->Text = L"Enter";
			this->moveButton->UseVisualStyleBackColor = false;
			this->moveButton->Click += gcnew System::EventHandler(this, &GUIInterface::moveButton_Click);
			// 
			// confirmButton
			// 
			this->confirmButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->confirmButton->AutoSize = true;
			this->confirmButton->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->confirmButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->confirmButton->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->confirmButton->Location = System::Drawing::Point(435, 120);
			this->confirmButton->Name = L"confirmButton";
			this->confirmButton->Size = System::Drawing::Size(147, 43);
			this->confirmButton->TabIndex = 1;
			this->confirmButton->Text = L"Confirm";
			this->confirmButton->UseVisualStyleBackColor = false;
			this->confirmButton->Click += gcnew System::EventHandler(this, &GUIInterface::confirmButton_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(299, 67);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(283, 28);
			this->comboBox1->TabIndex = 0;
			// 
			// haltButton
			// 
			this->haltButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->haltButton->AutoSize = true;
			this->haltButton->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->haltButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->haltButton->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->haltButton->Location = System::Drawing::Point(435, 539);
			this->haltButton->Name = L"haltButton";
			this->haltButton->Size = System::Drawing::Size(147, 42);
			this->haltButton->TabIndex = 6;
			this->haltButton->Text = L"haltMoving";
			this->haltButton->UseVisualStyleBackColor = false;
			this->haltButton->Click += gcnew System::EventHandler(this, &GUIInterface::haltButton_Click);
			// 
			// setHomeButton
			// 
			this->setHomeButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->setHomeButton->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->setHomeButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->setHomeButton->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->setHomeButton->Location = System::Drawing::Point(227, 539);
			this->setHomeButton->Name = L"setHomeButton";
			this->setHomeButton->Size = System::Drawing::Size(152, 42);
			this->setHomeButton->TabIndex = 5;
			this->setHomeButton->Text = L"setHome";
			this->setHomeButton->UseVisualStyleBackColor = false;
			this->setHomeButton->Click += gcnew System::EventHandler(this, &GUIInterface::setHomeButton_Click);
			// 
			// calculateButton
			// 
			this->calculateButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->calculateButton->AutoSize = true;
			this->calculateButton->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->calculateButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->calculateButton->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->calculateButton->Location = System::Drawing::Point(12, 539);
			this->calculateButton->Name = L"calculateButton";
			this->calculateButton->Size = System::Drawing::Size(147, 42);
			this->calculateButton->TabIndex = 4;
			this->calculateButton->Text = L"Calculate";
			this->calculateButton->UseVisualStyleBackColor = false;
			this->calculateButton->Click += gcnew System::EventHandler(this, &GUIInterface::calculateButton_Click);
			// 
			// displayBox
			// 
			this->displayBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->displayBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->displayBox->Location = System::Drawing::Point(12, 595);
			this->displayBox->Multiline = true;
			this->displayBox->Name = L"displayBox";
			this->displayBox->ReadOnly = true;
			this->displayBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->displayBox->Size = System::Drawing::Size(570, 335);
			this->displayBox->TabIndex = 7;
			this->displayBox->Text = L"\r\n";
			// 
			// GUIInterface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(594, 944);
			this->Controls->Add(this->displayBox);
			this->Controls->Add(this->setHomeButton);
			this->Controls->Add(this->haltButton);
			this->Controls->Add(this->calculateButton);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->confirmButton);
			this->Controls->Add(this->moveButton);
			this->Controls->Add(this->movementTextBox2);
			this->Controls->Add(this->distanceLabel);
			this->Controls->Add(this->poartLabel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(616, 874);
			this->Name = L"GUIInterface";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Automation program";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	//event: confirm button is clicked. 
	private: System::Void confirmButton_Click(System::Object^  sender, System::EventArgs^  e);
	//event: when the move button is clicked 
	private: System::Void moveButton_Click(System::Object^  sender, System::EventArgs^  e);
	//event: when the calculate button is clicked 
	private: System::Void calculateButton_Click(System::Object^  sender, System::EventArgs^  e);
	//event when the setHome button is clicked 
	private: System::Void setHomeButton_Click(System::Object^  sender, System::EventArgs^  e);
	//when the stop button is click.stop the actuator instantly
	private: System::Void haltButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void initialising (string machineName, string userName, string serialNo);
	private: System::Void checkingCSV(string machineName, string userName, string serialNo);
	private: System::Void movingHome();
	};
}
