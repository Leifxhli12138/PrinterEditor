#ifndef ENUMS_H
#define ENUMS_H

namespace PrinterEdit3_0 {

static const int SELECTION_HANDLE_SIZE_HALF=5;
static const int SELECTION_HANDLE_SIZE = 10;
static const int SELECTION_MARGIN = 10 ;


enum SelectionHandleState { SelectionHandleOff, SelectionHandleInactive, SelectionHandleActive };
enum SelectMode { none, netSelect,  move, size,  rotate };
enum ItemShape { selection , line , rectangle , roundrect , text,text2,ellipse , poly };

}
#endif // ENUMS_H
