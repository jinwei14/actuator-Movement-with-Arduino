#pragma once
#include <windows.h>
#include "iostream"
#include <string>
#include "GUIInterface.h"
namespace UserInputControl {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for inputBox
	/// </summary>
	public ref class inputBox : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Form ^ mainForm;
	public:
		inputBox(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~inputBox()
		{
			if (components)
			{
				delete components;
			}

		}
		//GUI component 
	private: System::Windows::Forms::TextBox^  userNamtextBox2;
	private: System::Windows::Forms::TextBox^  SerialtextBox3;
	private: System::Windows::Forms::Button^  confirmButton1;
	protected:

	private: System::Windows::Forms::Button^  clearButton2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  PowertextBox4;
	private: System::Windows::Forms::TextBox^  machineNamtextBox1;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(inputBox::typeid));
			this->userNamtextBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SerialtextBox3 = (gcnew System::Windows::Forms::TextBox());
			this->confirmButton1 = (gcnew System::Windows::Forms::Button());
			this->clearButton2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->PowertextBox4 = (gcnew System::Windows::Forms::TextBox());
			this->machineNamtextBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// userNamtextBox2
			// 
			this->userNamtextBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->userNamtextBox2->BackColor = System::Drawing::Color::Gainsboro;
			this->userNamtextBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->userNamtextBox2->Font = (gcnew System::Drawing::Font(L"Calibri", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->userNamtextBox2->Location = System::Drawing::Point(360, 95);
			this->userNamtextBox2->Name = L"userNamtextBox2";
			this->userNamtextBox2->Size = System::Drawing::Size(234, 34);
			this->userNamtextBox2->TabIndex = 1;
			// 
			// SerialtextBox3
			// 
			this->SerialtextBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->SerialtextBox3->BackColor = System::Drawing::Color::Gainsboro;
			this->SerialtextBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->SerialtextBox3->Font = (gcnew System::Drawing::Font(L"Calibri", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SerialtextBox3->Location = System::Drawing::Point(360, 166);
			this->SerialtextBox3->Name = L"SerialtextBox3";
			this->SerialtextBox3->Size = System::Drawing::Size(234, 34);
			this->SerialtextBox3->TabIndex = 2;
			// 
			// confirmButton1
			// 
			this->confirmButton1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->confirmButton1->AutoSize = true;
			this->confirmButton1->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->confirmButton1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->confirmButton1->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->confirmButton1->Location = System::Drawing::Point(401, 337);
			this->confirmButton1->Name = L"confirmButton1";
			this->confirmButton1->Size = System::Drawing::Size(193, 43);
			this->confirmButton1->TabIndex = 4;
			this->confirmButton1->Text = L"Confirm";
			this->confirmButton1->UseVisualStyleBackColor = false;
			this->confirmButton1->Click += gcnew System::EventHandler(this, &inputBox::confirmButton1_Click);
			// 
			// clearButton2
			// 
			this->clearButton2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->clearButton2->AutoSize = true;
			this->clearButton2->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->clearButton2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->clearButton2->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->clearButton2->Location = System::Drawing::Point(17, 337);
			this->clearButton2->Name = L"clearButton2";
			this->clearButton2->Size = System::Drawing::Size(183, 43);
			this->clearButton2->TabIndex = 17;
			this->clearButton2->Text = L"Clear All";
			this->clearButton2->UseVisualStyleBackColor = false;
			this->clearButton2->Click += gcnew System::EventHandler(this, &inputBox::clearButton2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label1->Font = (gcnew System::Drawing::Font(L"Cooper Black", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(197, 27);
			this->label1->TabIndex = 13;
			this->label1->Text = L"Machine Name:";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label2->Font = (gcnew System::Drawing::Font(L"Cooper Black", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 102);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(152, 27);
			this->label2->TabIndex = 18;
			this->label2->Text = L"User Name:";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label3->Font = (gcnew System::Drawing::Font(L"Cooper Black", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(12, 167);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(213, 27);
			this->label3->TabIndex = 19;
			this->label3->Text = L"Beamgage Serial";
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label4->Font = (gcnew System::Drawing::Font(L"Cooper Black", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(12, 235);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(280, 27);
			this->label4->TabIndex = 21;
			this->label4->Text = L"Intial Power (50-100):";
			// 
			// PowertextBox4
			// 
			this->PowertextBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->PowertextBox4->BackColor = System::Drawing::Color::Gainsboro;
			this->PowertextBox4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->PowertextBox4->Font = (gcnew System::Drawing::Font(L"Calibri", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PowertextBox4->Location = System::Drawing::Point(360, 235);
			this->PowertextBox4->Name = L"PowertextBox4";
			this->PowertextBox4->Size = System::Drawing::Size(234, 34);
			this->PowertextBox4->TabIndex = 3;
			// 
			// machineNamtextBox1
			// 
			this->machineNamtextBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->machineNamtextBox1->BackColor = System::Drawing::Color::Gainsboro;
			this->machineNamtextBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->machineNamtextBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->machineNamtextBox1->Location = System::Drawing::Point(360, 33);
			this->machineNamtextBox1->Name = L"machineNamtextBox1";
			this->machineNamtextBox1->Size = System::Drawing::Size(234, 34);
			this->machineNamtextBox1->TabIndex = 0;
			// 
			// inputBox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->ClientSize = System::Drawing::Size(606, 401);
			this->Controls->Add(this->PowertextBox4);
			this->Controls->Add(this->machineNamtextBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->clearButton2);
			this->Controls->Add(this->confirmButton1);
			this->Controls->Add(this->SerialtextBox3);
			this->Controls->Add(this->userNamtextBox2);
			//this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(628, 457);
			this->MinimumSize = System::Drawing::Size(628, 457);
			this->Name = L"inputBox";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"inputBox";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//all the method are defined here mainprogram should be the main cpp file 
	private: System::Void clearButton2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void confirmButton1_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
