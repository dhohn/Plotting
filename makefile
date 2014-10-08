

all: makeNewTree makePlots makePlotsMVA

makeNewTree: HWWtree.C HWWtree.h
	g++ -o $@ makeNewTree.C -I`root-config --incdir` `root-config --glibs` -I/user/dhohn/bin


makePlots: plotVar.C makePlots.C
	g++ -g -o $@ $@.C -I`root-config --incdir` `root-config --glibs` -I/user/dhohn/bin

makePlotsMVA: plotVarMVA.C makePlotsMVA.C
	g++ -g -o $@ $@.C -I`root-config --incdir` `root-config --glibs` -I/user/dhohn/bin

makeHistos: makeHistos.C
	g++ -g -o $@ $@.C -I`root-config --incdir` `root-config --glibs` -I${HOME}/Plotting
