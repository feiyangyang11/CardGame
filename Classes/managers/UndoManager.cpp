#include"UndoManager.h"


void UndoManager::save(UndoModel& model) {
	undoStack.push_back(model);
}
UndoModel& UndoManager::undo() {
	if (undoStack.empty()) {
		return UndoModel();
	}
	UndoModel lastModel = undoStack.back();
	undoStack.pop_back();
	return lastModel;
}
UndoModel& UndoManager::peek() {
	if (undoStack.empty()) {
		return UndoModel();
	}
	return undoStack.back();
}
bool UndoManager::canUndo() {
	return undoStack.size() > 0;
}
int UndoManager::getUndoSize() {
	return undoStack.size();
}
void UndoManager::clear() {
	undoStack.clear();
}