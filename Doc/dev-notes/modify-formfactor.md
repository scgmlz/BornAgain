#### How to make an API change that involves a form factor

This note shall help when you
* add a form factor
* remove a form factor
* change a form factor's argument list

After adding or removing a form factor, the following files need to be updated:
* Core/Basics/BornAgainNamespace.h
* Core/Parametrization/INodeVisitor.h (in two places)
* Core/includeIncludes/HardParticles.h
* Wrap/swig/libBornAgainCore.i (in two places: #include and %include)

Possibly, the form factor appears in
* Tests/UnitTests/Core/Sample/FormFactorBasicTest.cpp
* Core/StandardSamples/SampleComponents.cpp
* Core/StandardSamples/...

Examples and tests, e.g.:
* Examples/python/simulation/ex01_BasicParticles/AllFormFactorsAvailable.py
* Examples/python/simulation/...
* Tests/UnitTests/Core/Sample/FormFactorBasicTest.cpp
* Tests/UnitTests/GUI/TestGUICoreObjectCorrespondence.cpp
* Tests/ReferenceData/Core/FormFactors_*
* Tests/ReferenceData/Core/FormFactorsWithAbsorption_*

If the form factor is supported by the GUI, then also:
* GUI/coregui/Models/GroupInfoCatalogue.cpp
* GUI/coregui/Models/item_constants.h
* GUI/coregui/Models/FormFactorItems.h and .cpp
* GUI/coregui/Models/GUIDomainSampleVisitor.h and .cpp
* GUI/coregui/Models/ItemCatalogue.cpp
* GUI/coregui/Models/item_constants.h
* GUI/coregui/Views/RealSpaceWidgets/RealSpaceMesoCrystalUtils.cpp
* GUI/coregui/Views/widgetbox/widgetbox.qrc
* GUI/coregui/Views/widgetbox/widgetbox.xml

If there is a real-space view:
* GUI/coregui/Models/item_constants.h
* GUI/ba3d/ba3d/model/model.cpp
* GUI/ba3d/ba3d/model/particles.h and .cpp
* GUI/coregui/Views/RealSpaceWidgets/RealSpaceMesoCrystalUtils.cpp
* GUI/coregui/Views/RealSpaceWidgets/TransformTo3D.cpp

Recreate bindings with `cmake -DAUTOGENERATE=ON ..`