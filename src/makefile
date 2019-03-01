CC = gcc
GXX = g++ -std=c++11
#+ -s -O3 
CFLAGS = -Wall -Werror -s -O3 -mthreads -mwindows -DHAVE_W32API_H -D__WXMSW__ -D_UNICODE $(WXHDIR) -Wno-ctor-dtor-privacy -pipe -fmessage-length=0 -static-libgcc -static-libstdc++
LIBS = $(WXLDIR) -lwxmsw30u_xrc -lwxmsw30u_html -lwxmsw30u_adv -lwxmsw30u_core -lwxbase30u_xml -lwxbase30u_net -lwxbase30u -lwxtiff -lwxjpeg -lwxpng -lwxzlib -lwxregexu -lwxexpat -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwxregexu -lwinspool -lwinmm -lshell32 -lcomctl32 -lole32 -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32
WXHDIR = -IC:\dev\wxWidgets-3.0.2\lib\gcc_lib\mswu -IC:\development\wxWidgets-3.0.2\include
WXLDIR = -LC:\dev\wxWidgets-3.0.2\lib\gcc_lib
VPATH = file model-data view view-data model-plan view-plan controller-plan export import update
#all together
#-Wall -Werror -s -mthreads -mwindows -DHAVE_W32API_H -D__WXMSW__ -D_UNICODE -IC:\development\wxWidgets-3.0.2\lib\gcc_lib\mswu -IC:\development\wxWidgets-3.0.2\include -Wno-ctor-dtor-privacy -pipe -fmessage-length=0 -static-libgcc -static-libstdc++ -LC:\development\wxWidgets-3.0.2\lib\gcc_lib -lwxmsw30u_xrc -lwxmsw30u_html -lwxmsw30u_adv -lwxmsw30u_core -lwxbase30u_xml -lwxbase30u_net -lwxbase30u -lwxtiff -lwxjpeg -lwxpng -lwxzlib -lwxregexu -lwxexpat -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwxregexu -lwinspool -lwinmm -lshell32 -lcomctl32 -lole32 -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32
#for release: compile statically linked libs with -ffunction-sections -fdata-sections -Os, link with -Wl --gcc-sections, afterwards strip --strip-all

OBJ = MiniPlaner.rco \
    Dienst.o Messdiener.o Einzeltermin.o Serientermin.o MGruppe.o TGruppe.o Fehlzeit.o \
    DienstePanel.o MinisPanel.o TerminePanel.o MGruppenPanel.o TGruppenPanel.o FehlzeitenPanel.o DeleteDialog.o \
    DienstDialog.o MiniDialog.o EinzelterminDialog.o SerienterminDialog.o TerminDienstDialog.o MGruppeDialog.o TGruppeDialog.o FehlzeitDialog.o \
    PMessdiener.o PTermin.o CTermin.o PMGruppe.o PFehlzeit.o Planer.o PlanerInfo.o TerminCreator.o \
    PlaenePanel.o TerminePlanerDialog.o PTerminDienstDialog.o PlanPlanerDialog.o CloseDialog.o PMiniChoiceDialog.o PTerminDialog.o PlanFileHandler.o PlanerController.o \
    ExportLayoutDialog.o ExportLayout.o HTMLExport.o CSVExport.o ExcelXMLExport.o \
    MiniExportDialog.o PlanerSettingsDialog.o MiniImportDialog.o MiniExtrasDialog.o EinzelterminImportDialog.o \
    AboutPanel.o \
    UpdateChecker.o \
    PlanerMiniInterfaceDialog.o \
    Util.o DataFileHandler.o R.o MainFrame.o App.o

main: $(OBJ)
	$(GXX) $(CFLAGS) MiniPlaner.cpp -o MiniPlaner $(OBJ) $(LIBS)

MiniPlaner.rco:
	windres --use-temp-file -iMiniPlaner.rc -oMiniPlaner.rco $(WXHDIR)

%.o: %.cpp
	$(GXX) $(CFLAGS) -c $< -o $@ $(WXHDIR)
	
clean:
	del *.o *.rco