project('MiniPlaner', 'cpp',
    license : 'GPL3',
    version : '2.0.4',
    default_options : ['cpp_std=c++11']
)

miniplaner_src = files(
    'src/App.cpp',
    'src/MiniPlaner.cpp',
    'src/R.cpp',
    'src/Util.cpp',
    'src/controller-plan/PlanerController.cpp',
    'src/controller-plan/TerminCreator.cpp',
    'src/export/CSVExport.cpp',
    'src/export/ExcelXMLExport.cpp',
    'src/export/ExportLayout.cpp',
    'src/export/ExportLayoutDialog.cpp',
    'src/export/HTMLExport.cpp',
    'src/export/MiniExportDialog.cpp',
    'src/export/PlanerMiniInterfaceDialog.cpp',
    'src/file/DataFileHandler.cpp',
    'src/file/PlanFileHandler.cpp',
    'src/import/EinzelterminImportDialog.cpp',
    'src/import/MiniImportDialog.cpp',
    'src/model-data/Dienst.cpp',
    'src/model-data/Einzeltermin.cpp',
    'src/model-data/Fehlzeit.cpp',
    'src/model-data/MGruppe.cpp',
    'src/model-data/Messdiener.cpp',
    'src/model-data/Serientermin.cpp',
    'src/model-data/TGruppe.cpp',
    'src/model-plan/CTermin.cpp',
    'src/model-plan/PFehlzeit.cpp',
    'src/model-plan/PMGruppe.cpp',
    'src/model-plan/PMessdiener.cpp',
    'src/model-plan/PTermin.cpp',
    'src/model-plan/Planer.cpp',
    'src/model-plan/PlanerInfo.cpp',
    'src/update/UpdateChecker.cpp',
    'src/view-data/DeleteDialog.cpp',
    'src/view-data/DienstDialog.cpp',
    'src/view-data/DienstePanel.cpp',
    'src/view-data/EinzelterminDialog.cpp',
    'src/view-data/FehlzeitDialog.cpp',
    'src/view-data/FehlzeitenPanel.cpp',
    'src/view-data/MGruppeDialog.cpp',
    'src/view-data/MGruppenPanel.cpp',
    'src/view-data/MiniDialog.cpp',
    'src/view-data/MiniExtrasDialog.cpp',
    'src/view-data/MinisPanel.cpp',
    'src/view-data/SerienterminDialog.cpp',
    'src/view-data/TGruppeDialog.cpp',
    'src/view-data/TGruppenPanel.cpp',
    'src/view-data/TerminDienstDialog.cpp',
    'src/view-data/TerminePanel.cpp',
    'src/view-plan/CloseDialog.cpp',
    'src/view-plan/PMiniChoiceDialog.cpp',
    'src/view-plan/PTerminDialog.cpp',
    'src/view-plan/PTerminDienstDialog.cpp',
    'src/view-plan/PlaenePanel.cpp',
    'src/view-plan/PlanPlanerDialog.cpp',
    'src/view-plan/PlanerSettingsDialog.cpp',
    'src/view-plan/TerminePlanerDialog.cpp',
    'src/view/AboutPanel.cpp',
    'src/view/MainFrame.cpp'
)

wx_dep = dependency('wxwidgets', version : '>=3.0.4')

if host_machine.system() == 'windows'
    res_inc = include_directories(
        'src/img'
    )
    res_dep_files = files(
        'src/img/minis.ico',
    )
    raw_wx_windres_args = wx_dep.get_variable(configtool : 'rescomp').split()
    wx_windres_args = []
    foreach arg : raw_wx_windres_args
        if arg != 'windres'
            wx_windres_args += arg
        endif
    endforeach
    windows = import('windows')
    miniplaner_src += windows.compile_resources('res/resources.rc',
        args : wx_windres_args,
        depend_files : res_dep_files,
        include_directories : res_inc
    )
endif

executable('miniplaner', miniplaner_src,
  dependencies : [wx_dep],
  install : true
)
