#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H
#include<vector>
#include<stack>
#include"../models/UndoModel.h"
#include"../utils/CardTransform.h"
class UndoManager {
	//friend class UndoModel;
private:
	std::vector<UndoModel>undoStack;
public:
	void save(UndoModel& model);//¼ÓÈë
	UndoModel& undo();//»Ø¹ö
	UndoModel& peek();
	bool canUndo();
	int getUndoSize();
	void clear();
};
#endif