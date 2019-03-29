#pragma once
#include <string>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <sstream>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <vector>
#include "aboutPage.h"

namespace RTSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;
	using namespace std;

	int H_MIN = 0, H_MAX = 256;
	int S_MIN = 0, S_MAX = 256;
	int V_MIN = 0, V_MAX = 256;

	int x = 0;

	int red = 0, green = 255, blue = 0;

	const string windowName1 = "HSV Image";
	const string windowName2 = "Thresholded Image";
	const string windowName3 = "Gila Bend Airport";
	const string windowName4 = "Contours";

	Mat src, HSV, threshold, dst, cntrs;

	void setValues(int a, int b, int c, int d, int e, int f) {
		H_MIN = a;
		H_MAX = b;
		S_MIN = c;
		S_MAX = d;
		V_MIN = e;
		V_MAX = f;
	}

	void morphOps(Mat &thresh, int x) {

		Mat erodeElement = getStructuringElement(MORPH_RECT, cv::Size(x, x));
		Mat dilateElement = getStructuringElement(MORPH_RECT, cv::Size(10, 10));

		erode(thresh, thresh, erodeElement);
		erode(thresh, thresh, erodeElement);

		dilate(thresh, thresh, dilateElement);
		dilate(thresh, thresh, dilateElement);
	}

	void loopProg(int selection = 0) {
		switch (selection) {
		case 1:
			setValues(77, 256, 28, 256, 0, 256); x = 5;
			break;
		case 2:
			setValues(26, 100, 30, 133, 75, 153); x = 5;
			break;
		case 3:
			setValues(0, 256, 0, 35, 172, 202); x = 5;
			break;
		case 4:
			setValues(0, 256, 63, 256, 0, 256); x = 5;
			break;
		case 5:
			setValues(89, 105, 4, 70, 149, 217); x = 3;
			break;
		case 6:
			setValues(44, 79, 0, 18, 63, 256); x = 5;
			break;
		case 7:
			setValues(0, 256, 0, 256, 0, 79); x = 5;
			break;
		case 8:
			setValues(0, 256, 32, 39, 160, 196); x = 5;
			break;
		}
		cvtColor(src, HSV,COLOR_BGR2HSV);

		inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
		morphOps(threshold, x);

		vector<vector<cv::Point> > contours;
		vector<Vec4i> hierarchy;

		findContours(threshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
		vector<vector<cv::Point> > contours_poly(contours.size());
		vector<Rect> boundRect(contours.size());
		vector<Point2f>center(contours.size());
		vector<float>radius(contours.size());
		for (size_t i = 0; i < contours.size(); i++)
		{
			approxPolyDP(contours[i], contours_poly[i], 3, true);
			boundRect[i] = boundingRect(contours_poly[i]);
			minEnclosingCircle(contours_poly[i], center[i], radius[i]);
		}
		Mat drawing = Mat::zeros(threshold.size(), CV_8UC3);
		src.copyTo(dst);

		for (size_t i = 0; i< contours.size(); i++)
		{
			Scalar color = Scalar(blue, green, red);
			drawContours(drawing, contours_poly, (int)i, color, 1, 8, vector<Vec4i>(), 0, cv::Point());
			rectangle(dst, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
			rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
			circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
		}
		drawing.copyTo(cntrs);
		imshow(windowName3, dst);
	}

	/// <summary>
	/// Summary for mainForm
	/// </summary>
	public ref class mainForm : public System::Windows::Forms::Form
	{
	public:
		mainForm(void)
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
		~mainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton7;
	private: System::Windows::Forms::RadioButton^  radioButton8;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::RadioButton^  radioButton3;


	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  menuToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  viewsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  view1ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  view2ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  view3ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  regionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aircraftYardToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  asdToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  passengerServiceAreaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  storesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  controlCentersToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  runnawayToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  flightAndPassengerAffairsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  residenceAreaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem1;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  changeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  redToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  greenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  blueToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  hSVImageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hSVImageToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  showContoursToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  thresholdedImageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::RadioButton^  radioButton2;




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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(mainForm::typeid));
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton8 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->menuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->view1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->view2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->view3ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->regionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aircraftYardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->asdToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->passengerServiceAreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->storesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->controlCentersToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->runnawayToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->flightAndPassengerAffairsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->residenceAreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->greenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->blueToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->hSVImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hSVImageToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showContoursToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->thresholdedImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->BackColor = System::Drawing::Color::PowderBlue;
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Eras Medium ITC", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"View 1", L"View 2", L"View 3" });
			this->comboBox1->Location = System::Drawing::Point(41, 31);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(192, 26);
			this->comboBox1->TabIndex = 1;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &mainForm::comboBox1_SelectedIndexChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::Transparent;
			this->groupBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Eras Bold ITC", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox1->ForeColor = System::Drawing::Color::Cyan;
			this->groupBox1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->groupBox1->Location = System::Drawing::Point(7, 33);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(8);
			this->groupBox1->Size = System::Drawing::Size(281, 142);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Select a view";
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(175)), static_cast<System::Int32>(static_cast<System::Byte>(5)),
				static_cast<System::Int32>(static_cast<System::Byte>(5)));
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(142, 63);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(104, 68);
			this->button2->TabIndex = 6;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &mainForm::button2_Click_1);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button1->Enabled = false;
			this->button1->Location = System::Drawing::Point(28, 63);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(108, 68);
			this->button1->TabIndex = 5;
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &mainForm::button1_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::Transparent;
			this->groupBox2->Controls->Add(this->radioButton1);
			this->groupBox2->Controls->Add(this->radioButton6);
			this->groupBox2->Controls->Add(this->radioButton7);
			this->groupBox2->Controls->Add(this->radioButton8);
			this->groupBox2->Controls->Add(this->radioButton5);
			this->groupBox2->Controls->Add(this->radioButton4);
			this->groupBox2->Controls->Add(this->radioButton3);
			this->groupBox2->Controls->Add(this->radioButton2);
			this->groupBox2->Enabled = false;
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Eras Bold ITC", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox2->ForeColor = System::Drawing::Color::Cyan;
			this->groupBox2->Location = System::Drawing::Point(8, 183);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(280, 158);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Track Region";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton1->Location = System::Drawing::Point(13, 27);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(110, 22);
			this->radioButton1->TabIndex = 7;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Aircraft Yard";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &mainForm::radioButton1_CheckedChanged_1);
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton6->Location = System::Drawing::Point(13, 73);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(125, 22);
			this->radioButton6->TabIndex = 8;
			this->radioButton6->TabStop = true;
			this->radioButton6->Text = L"Residence Area";
			this->radioButton6->UseVisualStyleBackColor = true;
			this->radioButton6->CheckedChanged += gcnew System::EventHandler(this, &mainForm::radioButton6_CheckedChanged);
			// 
			// radioButton7
			// 
			this->radioButton7->AutoSize = true;
			this->radioButton7->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton7->Location = System::Drawing::Point(13, 122);
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->Size = System::Drawing::Size(203, 22);
			this->radioButton7->TabIndex = 8;
			this->radioButton7->TabStop = true;
			this->radioButton7->Text = L"Flight and Passenger Affairs";
			this->radioButton7->UseVisualStyleBackColor = true;
			this->radioButton7->CheckedChanged += gcnew System::EventHandler(this, &mainForm::radioButton7_CheckedChanged);
			// 
			// radioButton8
			// 
			this->radioButton8->AutoSize = true;
			this->radioButton8->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton8->Location = System::Drawing::Point(13, 50);
			this->radioButton8->Name = L"radioButton8";
			this->radioButton8->Size = System::Drawing::Size(97, 22);
			this->radioButton8->TabIndex = 8;
			this->radioButton8->TabStop = true;
			this->radioButton8->Text = L"Runnaway";
			this->radioButton8->UseVisualStyleBackColor = true;
			this->radioButton8->CheckedChanged += gcnew System::EventHandler(this, &mainForm::radioButton8_CheckedChanged);
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton5->Location = System::Drawing::Point(144, 50);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(130, 22);
			this->radioButton5->TabIndex = 8;
			this->radioButton5->TabStop = true;
			this->radioButton5->Text = L"Control Centers";
			this->radioButton5->UseVisualStyleBackColor = true;
			this->radioButton5->CheckedChanged += gcnew System::EventHandler(this, &mainForm::radioButton5_CheckedChanged);
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton4->Location = System::Drawing::Point(144, 27);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(66, 22);
			this->radioButton4->TabIndex = 8;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"Stores";
			this->radioButton4->UseVisualStyleBackColor = true;
			this->radioButton4->CheckedChanged += gcnew System::EventHandler(this, &mainForm::radioButton4_CheckedChanged);
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton3->Location = System::Drawing::Point(13, 97);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(169, 22);
			this->radioButton3->TabIndex = 8;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Passenger Service Area";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &mainForm::radioButton3_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton2->Location = System::Drawing::Point(144, 73);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(76, 22);
			this->radioButton2->TabIndex = 8;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Garden";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &mainForm::radioButton2_CheckedChanged);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::Color::RoyalBlue;
			this->menuStrip1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->menuToolStripMenuItem,
					this->toolsToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(296, 28);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// menuToolStripMenuItem
			// 
			this->menuToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->viewsToolStripMenuItem,
					this->regionsToolStripMenuItem, this->toolStripSeparator2, this->exitToolStripMenuItem1
			});
			this->menuToolStripMenuItem->ForeColor = System::Drawing::SystemColors::Window;
			this->menuToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Black;
			this->menuToolStripMenuItem->Name = L"menuToolStripMenuItem";
			this->menuToolStripMenuItem->Size = System::Drawing::Size(58, 24);
			this->menuToolStripMenuItem->Text = L"Menu";
			// 
			// viewsToolStripMenuItem
			// 
			this->viewsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->view1ToolStripMenuItem,
					this->view2ToolStripMenuItem, this->view3ToolStripMenuItem
			});
			this->viewsToolStripMenuItem->Name = L"viewsToolStripMenuItem";
			this->viewsToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->viewsToolStripMenuItem->Text = L"Views";
			// 
			// view1ToolStripMenuItem
			// 
			this->view1ToolStripMenuItem->Name = L"view1ToolStripMenuItem";
			this->view1ToolStripMenuItem->Size = System::Drawing::Size(128, 26);
			this->view1ToolStripMenuItem->Text = L"View 1";
			this->view1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::view1ToolStripMenuItem_Click);
			// 
			// view2ToolStripMenuItem
			// 
			this->view2ToolStripMenuItem->Name = L"view2ToolStripMenuItem";
			this->view2ToolStripMenuItem->Size = System::Drawing::Size(128, 26);
			this->view2ToolStripMenuItem->Text = L"View 2";
			this->view2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::view2ToolStripMenuItem_Click);
			// 
			// view3ToolStripMenuItem
			// 
			this->view3ToolStripMenuItem->Name = L"view3ToolStripMenuItem";
			this->view3ToolStripMenuItem->Size = System::Drawing::Size(128, 26);
			this->view3ToolStripMenuItem->Text = L"View 3";
			this->view3ToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::view3ToolStripMenuItem_Click);
			// 
			// regionsToolStripMenuItem
			// 
			this->regionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
				this->aircraftYardToolStripMenuItem,
					this->asdToolStripMenuItem, this->passengerServiceAreaToolStripMenuItem, this->storesToolStripMenuItem, this->controlCentersToolStripMenuItem,
					this->runnawayToolStripMenuItem, this->flightAndPassengerAffairsToolStripMenuItem, this->residenceAreaToolStripMenuItem
			});
			this->regionsToolStripMenuItem->Enabled = false;
			this->regionsToolStripMenuItem->Name = L"regionsToolStripMenuItem";
			this->regionsToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->regionsToolStripMenuItem->Text = L"Regions";
			// 
			// aircraftYardToolStripMenuItem
			// 
			this->aircraftYardToolStripMenuItem->MergeIndex = 8;
			this->aircraftYardToolStripMenuItem->Name = L"aircraftYardToolStripMenuItem";
			this->aircraftYardToolStripMenuItem->Size = System::Drawing::Size(266, 26);
			this->aircraftYardToolStripMenuItem->Text = L"Aircraft Yard";
			this->aircraftYardToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::aircraftYardToolStripMenuItem_Click);
			// 
			// asdToolStripMenuItem
			// 
			this->asdToolStripMenuItem->Name = L"asdToolStripMenuItem";
			this->asdToolStripMenuItem->Size = System::Drawing::Size(266, 26);
			this->asdToolStripMenuItem->Text = L"Garden";
			this->asdToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::asdToolStripMenuItem_Click);
			// 
			// passengerServiceAreaToolStripMenuItem
			// 
			this->passengerServiceAreaToolStripMenuItem->Name = L"passengerServiceAreaToolStripMenuItem";
			this->passengerServiceAreaToolStripMenuItem->Size = System::Drawing::Size(266, 26);
			this->passengerServiceAreaToolStripMenuItem->Text = L"Passenger Service Area";
			this->passengerServiceAreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::passengerServiceAreaToolStripMenuItem_Click);
			// 
			// storesToolStripMenuItem
			// 
			this->storesToolStripMenuItem->MergeIndex = 2;
			this->storesToolStripMenuItem->Name = L"storesToolStripMenuItem";
			this->storesToolStripMenuItem->Size = System::Drawing::Size(266, 26);
			this->storesToolStripMenuItem->Text = L"Stores";
			this->storesToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::storesToolStripMenuItem_Click);
			// 
			// controlCentersToolStripMenuItem
			// 
			this->controlCentersToolStripMenuItem->Name = L"controlCentersToolStripMenuItem";
			this->controlCentersToolStripMenuItem->Size = System::Drawing::Size(266, 26);
			this->controlCentersToolStripMenuItem->Text = L"Control Centers";
			this->controlCentersToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::controlCentersToolStripMenuItem_Click);
			// 
			// runnawayToolStripMenuItem
			// 
			this->runnawayToolStripMenuItem->Name = L"runnawayToolStripMenuItem";
			this->runnawayToolStripMenuItem->Size = System::Drawing::Size(266, 26);
			this->runnawayToolStripMenuItem->Text = L"Runnaway";
			this->runnawayToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::runnawayToolStripMenuItem_Click);
			// 
			// flightAndPassengerAffairsToolStripMenuItem
			// 
			this->flightAndPassengerAffairsToolStripMenuItem->Name = L"flightAndPassengerAffairsToolStripMenuItem";
			this->flightAndPassengerAffairsToolStripMenuItem->Size = System::Drawing::Size(266, 26);
			this->flightAndPassengerAffairsToolStripMenuItem->Text = L"Flight and Passenger Affairs";
			this->flightAndPassengerAffairsToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::flightAndPassengerAffairsToolStripMenuItem_Click);
			// 
			// residenceAreaToolStripMenuItem
			// 
			this->residenceAreaToolStripMenuItem->Name = L"residenceAreaToolStripMenuItem";
			this->residenceAreaToolStripMenuItem->Size = System::Drawing::Size(266, 26);
			this->residenceAreaToolStripMenuItem->Text = L"Residence Area";
			this->residenceAreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::residenceAreaToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(213, 6);
			// 
			// exitToolStripMenuItem1
			// 
			this->exitToolStripMenuItem1->Name = L"exitToolStripMenuItem1";
			this->exitToolStripMenuItem1->Size = System::Drawing::Size(216, 26);
			this->exitToolStripMenuItem1->Text = L"Exit";
			this->exitToolStripMenuItem1->Click += gcnew System::EventHandler(this, &mainForm::exitToolStripMenuItem1_Click);
			// 
			// toolsToolStripMenuItem
			// 
			this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->changeToolStripMenuItem,
					this->toolStripSeparator1, this->hSVImageToolStripMenuItem
			});
			this->toolsToolStripMenuItem->ForeColor = System::Drawing::SystemColors::Window;
			this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
			this->toolsToolStripMenuItem->Size = System::Drawing::Size(53, 24);
			this->toolsToolStripMenuItem->Text = L"View";
			this->toolsToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::toolsToolStripMenuItem_Click);
			// 
			// changeToolStripMenuItem
			// 
			this->changeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->redToolStripMenuItem,
					this->greenToolStripMenuItem, this->blueToolStripMenuItem
			});
			this->changeToolStripMenuItem->Name = L"changeToolStripMenuItem";
			this->changeToolStripMenuItem->Size = System::Drawing::Size(229, 26);
			this->changeToolStripMenuItem->Text = L"Bounding shape color";
			// 
			// redToolStripMenuItem
			// 
			this->redToolStripMenuItem->Name = L"redToolStripMenuItem";
			this->redToolStripMenuItem->Size = System::Drawing::Size(123, 26);
			this->redToolStripMenuItem->Text = L"Red";
			this->redToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::redToolStripMenuItem_Click);
			// 
			// greenToolStripMenuItem
			// 
			this->greenToolStripMenuItem->Name = L"greenToolStripMenuItem";
			this->greenToolStripMenuItem->Size = System::Drawing::Size(123, 26);
			this->greenToolStripMenuItem->Text = L"Green";
			this->greenToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::greenToolStripMenuItem_Click);
			// 
			// blueToolStripMenuItem
			// 
			this->blueToolStripMenuItem->Name = L"blueToolStripMenuItem";
			this->blueToolStripMenuItem->Size = System::Drawing::Size(123, 26);
			this->blueToolStripMenuItem->Text = L"Blue";
			this->blueToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::blueToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(226, 6);
			// 
			// hSVImageToolStripMenuItem
			// 
			this->hSVImageToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->hSVImageToolStripMenuItem1,
					this->showContoursToolStripMenuItem, this->thresholdedImageToolStripMenuItem
			});
			this->hSVImageToolStripMenuItem->Name = L"hSVImageToolStripMenuItem";
			this->hSVImageToolStripMenuItem->Size = System::Drawing::Size(229, 26);
			this->hSVImageToolStripMenuItem->Text = L"More";
			// 
			// hSVImageToolStripMenuItem1
			// 
			this->hSVImageToolStripMenuItem1->Name = L"hSVImageToolStripMenuItem1";
			this->hSVImageToolStripMenuItem1->Size = System::Drawing::Size(212, 26);
			this->hSVImageToolStripMenuItem1->Text = L"HSV Image";
			this->hSVImageToolStripMenuItem1->Click += gcnew System::EventHandler(this, &mainForm::hSVImageToolStripMenuItem1_Click);
			// 
			// showContoursToolStripMenuItem
			// 
			this->showContoursToolStripMenuItem->Name = L"showContoursToolStripMenuItem";
			this->showContoursToolStripMenuItem->Size = System::Drawing::Size(212, 26);
			this->showContoursToolStripMenuItem->Text = L"Show Contours";
			this->showContoursToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::showContoursToolStripMenuItem_Click);
			// 
			// thresholdedImageToolStripMenuItem
			// 
			this->thresholdedImageToolStripMenuItem->Name = L"thresholdedImageToolStripMenuItem";
			this->thresholdedImageToolStripMenuItem->Size = System::Drawing::Size(212, 26);
			this->thresholdedImageToolStripMenuItem->Text = L"Thresholded Image";
			this->thresholdedImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::thresholdedImageToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			this->exitToolStripMenuItem->ForeColor = System::Drawing::SystemColors::Window;
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(53, 24);
			this->exitToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(131, 26);
			this->aboutToolStripMenuItem->Text = L"About..";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &mainForm::aboutToolStripMenuItem_Click);
			// 
			// mainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(120, 120);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->BackColor = System::Drawing::Color::DarkSlateGray;
			this->ClientSize = System::Drawing::Size(296, 347);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"mainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Region Tracking System";
			this->TransparencyKey = System::Drawing::Color::DarkBlue;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &mainForm::mainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &mainForm::mainForm_Load_1);
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void exitToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (MessageBox::Show("Are you sure want to exit?", "Warning!", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == Windows::Forms::DialogResult::Yes) {
		Application::Exit();
	}
}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	groupBox2->Enabled = true;
	regionsToolStripMenuItem->Enabled = true;
	if (comboBox1->SelectedIndex == 0) {
		button1->Enabled = false;
		button2->Enabled = true;
	}
	else if (comboBox1->SelectedIndex == 2) {
		button1->Enabled = true;
		button2->Enabled = false;
	}
	else {
		button1->Enabled = true;
		button2->Enabled = true;
	}
	switch (comboBox1->SelectedIndex) {
	case 0:
		src = imread("mapSampleg.jpg", IMREAD_COLOR);
		break;
	case 1:
		src = imread("mapSampleg1.jpg", IMREAD_COLOR);
		break;
	case 2:
		src = imread("mapSampleg2.jpg", IMREAD_COLOR);
		break;
	}
	if (!src.data) {
		groupBox2->Enabled = false;
		destroyAllWindows();
		MessageBox::Show("The View cannot be displayed. Please check the view and Try Again!", "Error!",MessageBoxButtons::OK, MessageBoxIcon::Error);
		goto h;
	}
	radioButton1->Checked = false;
	radioButton2->Checked = false;
	radioButton3->Checked = false;
	radioButton4->Checked = false;
	radioButton5->Checked = false;
	radioButton6->Checked = false;
	radioButton7->Checked = false;
	radioButton8->Checked = false;
	imshow(windowName3, src);
h:
	this->Focus();
}
private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	loopProg(1);
}
private: System::Void radioButton4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	loopProg(4);
}
private: System::Void radioButton8_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	loopProg(6);
}
private: System::Void radioButton5_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	loopProg(5);
}
private: System::Void radioButton6_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	loopProg(8);
}
private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	loopProg(2);
}
private: System::Void radioButton3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	loopProg(3);
}
private: System::Void radioButton7_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	loopProg(7);
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	comboBox1->SelectedIndex -= 1;
}

private: System::Void view1ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	comboBox1->SelectedIndex = 0;
}
private: System::Void view2ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	comboBox1->SelectedIndex = 1;
}
private: System::Void view3ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	comboBox1->SelectedIndex = 2;
}
private: System::Void aircraftYardToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	radioButton1->Checked = true;
}
private: System::Void radioButton9_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	loopProg(1);
}
private: System::Void radioButton1_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e) {
	loopProg(1);
}
private: System::Void button2_EnabledChanged(System::Object^  sender, System::EventArgs^  e) {
	comboBox1->Focus();
}
private: System::Void button2_Click_1(System::Object^  sender, System::EventArgs^  e) {
	comboBox1->SelectedIndex += 1;
	radioButton1->AutoCheck = false;
	radioButton1->AutoCheck = true;
}
private: System::Void asdToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	radioButton2->Checked = true;
}

private: System::Void mainForm_Load_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void runnawayToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	radioButton8->Checked = true;
}
private: System::Void passengerServiceAreaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	radioButton3->Checked = true;
}
private: System::Void storesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	radioButton4->Checked = true;
}
private: System::Void controlCentersToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	radioButton5->Checked = true;
}
private: System::Void flightAndPassengerAffairsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	radioButton7->Checked = true;
}
private: System::Void residenceAreaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	radioButton6->Checked = true;
}

private: System::Void thresholdedImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (threshold.data) { imshow(windowName2, threshold); }
	else { MessageBox::Show("Please make a selection.", "Cannot complete the Action!", MessageBoxButtons::OK, MessageBoxIcon::Exclamation); }
}
private: System::Void hSVImageToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (HSV.data) { imshow(windowName1, HSV); }
	else { MessageBox::Show("Please select a view.", "Cannot complete the Action!", MessageBoxButtons::OK, MessageBoxIcon::Exclamation); }
}
private: System::Void showContoursToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (cntrs.data) { imshow(windowName4, cntrs); }
	else { MessageBox::Show("Please make a selection.", "Cannot complete the Action!", MessageBoxButtons::OK, MessageBoxIcon::Exclamation); }
}
private: System::Void redToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	red = 255; green = 0; blue = 0;
}
private: System::Void greenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	red = 0; green = 255; blue = 0;
}
private: System::Void blueToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	red = 0; green = 0; blue = 255;
}
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	aboutPage^ p1 = gcnew aboutPage();
	p1->ShowDialog();
}
private: System::Void toolsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void mainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	if (MessageBox::Show("Are you sure want to exit?", "Warning!", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == Windows::Forms::DialogResult::No) {
		e->Cancel = true;
	}
}
};
}
