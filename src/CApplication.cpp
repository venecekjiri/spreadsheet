#include "CApplication.h"
#include "CSheet.h"
#include "CController.h"

void CApplication::Run() {

    CSheet sheet;
    CController controller(sheet);

    controller.Run();
}
