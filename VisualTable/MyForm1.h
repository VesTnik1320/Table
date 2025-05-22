#pragma once
#include "../Table/Table.h"
#include "../Table/ArrayTable.h"
#include "../Table/HashTable.h"
#include "../Table/TreeTable.h"
#include "../Table/SortTable.h"

namespace VisualTable {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MyForm : public Form {
    private:
        // Элементы управления
        DataGridView^ dataGridView;
        GroupBox^ tableTypeGroup;
        RadioButton^ arrayTableRadio;
        RadioButton^ hashTableRadio;
        RadioButton^ treeTableRadio;
        RadioButton^ sortedTableRadio;
        RadioButton^ listHashTableRadio;
        Button^ initButton;
        TextBox^ keyCountBox;
        TextBox^ valueRangeBox;
        Button^ searchButton;
        TextBox^ searchKeyBox;
        Button^ addSingleButton;

        Table<String^, int>* currentTable;

    public:
        MyForm() {
            InitializeComponent();
            currentTable = nullptr;
        }

        ~MyForm() {
            if (currentTable) delete currentTable;
        }

    private:
        void InitializeComponent() {
            // Настройка формы
            this->Text = "Table Visualizer";
            this->Size = Drawing::Size(800, 600);

            // Группа выбора таблицы
            tableTypeGroup = gcnew GroupBox();
            tableTypeGroup->Text = "Table Type";
            tableTypeGroup->Location = Point(20, 20);
            tableTypeGroup->Size = Drawing::Size(200, 150);

            arrayTableRadio = gcnew RadioButton();
            arrayTableRadio->Text = "Array Table";
            arrayTableRadio->Location = Point(10, 20);

            hashTableRadio = gcnew RadioButton();
            hashTableRadio->Text = "Array Hash Table";
            hashTableRadio->Location = Point(10, 45);

            treeTableRadio = gcnew RadioButton();
            treeTableRadio->Text = "Tree Table";
            treeTableRadio->Location = Point(10, 70);

            sortedTableRadio = gcnew RadioButton();
            sortedTableRadio->Text = "Sort Table";
            sortedTableRadio->Location = Point(10, 95);

            listHashTableRadio = gcnew RadioButton();
            listHashTableRadio->Text = "List Hash Table";
            listHashTableRadio->Location = Point(10, 120);

            tableTypeGroup->Controls->Add(arrayTableRadio);
            tableTypeGroup->Controls->Add(hashTableRadio);
            tableTypeGroup->Controls->Add(treeTableRadio);
            tableTypeGroup->Controls->Add(sortedTableRadio);
            tableTypeGroup->Controls->Add(listHashTableRadio);

            // Поля ввода
            Label^ keyCountLabel = gcnew Label();
            keyCountLabel->Text = "Key count:";
            keyCountLabel->Location = Point(240, 20);

            keyCountBox = gcnew TextBox();
            keyCountBox->Location = Point(320, 18);
            keyCountBox->Size = Drawing::Size(50, 20);
            keyCountBox->Text = "10";

            Label^ valueRangeLabel = gcnew Label();
            valueRangeLabel->Text = "Value max:";
            valueRangeLabel->Location = Point(380, 20);

            valueRangeBox = gcnew TextBox();
            valueRangeBox->Location = Point(460, 18);
            valueRangeBox->Size = Drawing::Size(50, 20);
            valueRangeBox->Text = "10";

            searchKeyBox = gcnew TextBox();
            searchKeyBox->Location = Point(280, 30);
            searchKeyBox->Text = "10";

            // DataGridView
            dataGridView = gcnew DataGridView();
            dataGridView->Location = Point(20, 150);
            dataGridView->Size = Drawing::Size(740, 400);
            dataGridView->Columns->Add("Key", "Key");
            dataGridView->Columns->Add("Value", "Value");

            // Добавление элементов на форму
            this->Controls->Add(tableTypeGroup);
            this->Controls->Add(dataGridView);
            this->Controls->Add(keyCountLabel);
            this->Controls->Add(keyCountBox);
            this->Controls->Add(valueRangeLabel);
            this->Controls->Add(valueRangeBox);

            // После создания RadioButton-ов:
            tableTypeGroup->Controls->Add(arrayTableRadio);
            tableTypeGroup->Controls->Add(hashTableRadio);
            tableTypeGroup->Controls->Add(treeTableRadio);
            tableTypeGroup->Controls->Add(sortedTableRadio);
            tableTypeGroup->Controls->Add(listHashTableRadio);

            // ... остальные элементы ...
        }

        Table<String^, int>* CreateSelectedTable() {
            if (arrayTableRadio->Checked)
                return new ArrayTable<String^, int>(100);
            // ... аналогично для других типов ...
            return nullptr;
        }

        void UpdateTableDisplay() {
            dataGridView->Rows->Clear();
            if (!currentTable) return;

            currentTable->Reset();
            while (!currentTable->IsEnd()) {
                auto record = currentTable->GetCurr();
                dataGridView->Rows->Add(record.key, record.value);
                currentTable->GoNext();
            }
        }

        void initButton_Click(Object^ sender, EventArgs^ e) {
            try {
                if (currentTable) delete currentTable;
                currentTable = CreateSelectedTable();

                int count = Int32::Parse(keyCountBox->Text);
                int maxVal = Int32::Parse(valueRangeBox->Text);

                Random^ rand = gcnew Random();
                for (int i = 0; i < count; i++) {
                    String^ key = "Key_" + i.ToString();
                    int value = rand->Next(1, maxVal);
                    currentTable->Insert(Record<String^, int>{key, value});
                }

                UpdateTableDisplay();
            }
            catch (Exception^ e) {
                MessageBox::Show("Error: " + e->Message);
            }
        }

        // ... другие обработчики ...
    };
}