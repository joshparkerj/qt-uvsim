#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UVSim.h"

#include "Driver.h"


class UVSim : public QMainWindow
{
	Q_OBJECT

public:
	UVSim(QWidget *parent = Q_NULLPTR);
	const int MEM_SIZE = 100;
	int* memory = new int[MEM_SIZE] { 0 };
	int accumulator = 0;
	Driver* driver = new Driver();
	void Execute();
	void Read(int operand);
	void Write(int operand);
	void Load(int operand);
	void Store(int operand);
	void Add(int operand);
	void Subtract(int operand);
	void Divide(int operand);
	void Multiply(int operand);
	void Branch(int& i, int operand);
	void BranchNeg(int& i, int operand);
	void BranchZero(int& i, int operand);
private slots:
	void pushButtonClicked();
private:
	Ui::UVSimClass ui;
};
