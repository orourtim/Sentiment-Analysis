all: Assign3.exe

Assign3.exe: ClassNode.o FeatureNode.o FeatureVector.o Preprocessor.o NaiveBayesClassifier.o main.o
	g++ -std=c++17 ClassNode.o FeatureNode.o FeatureVector.o Preprocessor.o NaiveBayesClassifier.o main.o -o Assign3.exe
	
ClassNode.o: ClassNode.cpp
	g++ -std=c++17 ClassNode.cpp -c
	
FeatureNode.o: FeatureNode.cpp
	g++ -std=c++17 FeatureNode.cpp -c

FeatureVector.o: FeatureVector.cpp
	g++ -std=c++17 FeatureVector.cpp -c

Preprocessor.o: Preprocessor.cpp
	g++ -std=c++17 Preprocessor.cpp -c

NaiveBayesClassifier.o: NaiveBayesClassifier.cpp
	g++ -std=c++17 NaiveBayesClassifier.cpp -c

main.o: main.cpp
	g++ -std=c++17 main.cpp -c

clean:
	del Assign3.exe ClassNode.o FeatureNode.o FeatureVector.o Preprocessor.o NaiveBayesClassifier.o main.o