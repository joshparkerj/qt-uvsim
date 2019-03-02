#include "UVSim.h"
#include <QInputDialog>

UVSim::UVSim(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(pushButtonClicked()));
}

void UVSim::pushButtonClicked()
{
	Execute();
}


void UVSim::Execute()
{
	QStringList qs = UVSim::ui.plainTextEdit_01->toPlainText().split('\n')
		+ UVSim::ui.plainTextEdit_03->toPlainText().split('\n')
		+ UVSim::ui.plainTextEdit_05->toPlainText().split('\n')
		+ UVSim::ui.plainTextEdit_07->toPlainText().split('\n')
		+ UVSim::ui.plainTextEdit_09->toPlainText().split('\n');
	QStringList::ConstIterator ci;
	int initializeMemory = 0;
	for (ci = qs.constBegin(); ci != qs.constEnd(); ++ci)
	{
		memory[initializeMemory] = ci->toInt();
		initializeMemory++;
	}
	for (int i = 0; i < 100; i++)
	{
		int opcode = memory[i] / 100;
		int operand = memory[i] % 100;
		switch (opcode)
		{
		case 10:
			this->Read(operand);
			break;
		case 11:
			this->Write(operand);
			break;
		case 20:
			this->Load(operand);
			break;
		case 21:
			this->Store(operand);
			break;
		case 30:
			this->Add(operand);
			break;
		case 31:
			this->Subtract(operand);
			break;
		case 32:
			this->Divide(operand);
			break;
		case 33:
			this->Multiply(operand);
			break;
		case 40:
			this->Branch(i, operand); //makes i equal to operand
			break;
		case 41:
			this->BranchNeg(i, operand);
			break;
		case 42:
			this->BranchZero(i, operand);
			break;
		case 43:
			return;
		default:
			std::cout << "Bad opcode" << std::endl;
			break;
		}
	}
	int dump = 0;
	while (dump < 20)
	{
		UVSim::ui.plainTextEdit_11->appendPlainText(QString::number(memory[dump]));
		UVSim::ui.plainTextEdit_11->appendPlainText(QString('\n'));
		dump++;
	}
	while (dump < 40)
	{
		UVSim::ui.plainTextEdit_13->appendPlainText(QString::number(memory[dump]));
		UVSim::ui.plainTextEdit_13->appendPlainText(QString('\n'));
		dump++;
	}
	while (dump < 60)
	{
		UVSim::ui.plainTextEdit_15->appendPlainText(QString::number(memory[dump]));
		UVSim::ui.plainTextEdit_15->appendPlainText(QString('\n'));
		dump++;
	}
	while (dump < 80)
	{
		UVSim::ui.plainTextEdit_17->appendPlainText(QString::number(memory[dump]));
		UVSim::ui.plainTextEdit_17->appendPlainText(QString('\n'));
		dump++;
	}
	while (dump < 100)
	{
		UVSim::ui.plainTextEdit_19->appendPlainText(QString::number(memory[dump]));
		UVSim::ui.plainTextEdit_19->appendPlainText(QString('\n'));
		dump++;
	}
}

void UVSim::Read(int operand)
{
	if (operand >= 0 && operand < MEM_SIZE)
		memory[operand] = QInputDialog::getText(this, "UVSim Input", "Input a number: ").toInt();
	else
		UVSim::ui.plainTextEdit_22->appendPlainText(QString("\nout of range!"));
}

void UVSim::Write(int operand)
{
	if (operand >= 0 && operand < MEM_SIZE)
		UVSim::ui.plainTextEdit_22->appendPlainText(QString('\n')+QString::number(memory[operand]));
	else
		UVSim::ui.plainTextEdit_22->appendPlainText(QString("\nout of range!"));
}

void UVSim::Load(int operand)
{
	if (operand >= 0 && operand < MEM_SIZE)
		accumulator = memory[operand];
	else
		UVSim::ui.plainTextEdit_22->appendPlainText(QString("\nout of range!"));
}

void UVSim::Store(int operand)
{
	if (operand >= 0 && operand < MEM_SIZE)
		memory[operand] = accumulator;
	else
		UVSim::ui.plainTextEdit_22->appendPlainText(QString("\nout of range!"));
}

void UVSim::Add(int operand)
{
	accumulator = driver->Add(accumulator, memory[operand]);
}

void UVSim::Subtract(int operand)
{
	accumulator = driver->Subtract(accumulator, memory[operand]);
}

void UVSim::Divide(int operand)
{
	accumulator = driver->Divide(accumulator, memory[operand]);
}

void UVSim::Multiply(int operand)
{
	accumulator = driver->Multiply(accumulator, memory[operand]);
}

void UVSim::Branch(int & i, int operand)
{
	if (operand >= 0 && operand < MEM_SIZE)
		i = operand - 1;
}

void UVSim::BranchNeg(int & i, int operand)
{
	if ((accumulator < 0) && (operand >= 0 && operand < MEM_SIZE))
		i = operand - 1;
}

void UVSim::BranchZero(int & i, int operand)
{
	if ((accumulator == 0) && (operand >= 0 && operand < MEM_SIZE))
		i = operand - 1;
}
