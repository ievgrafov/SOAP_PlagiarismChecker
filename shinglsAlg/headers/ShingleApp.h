#pragma once

#include "../headers/Shingles.h"
#include "../headers/ShingleAppLogger.h"
#include "../src/gsoap_autogenerated/soapshingleService.h"
#include "../include/threads.h"

using namespace std;
/*
main class. It provides receiving massages and its processing
*/
namespace DePlaguarism{
	struct Pair{
		unsigned int docId;
		float similarity;
		Pair (unsigned int _docId, float _similarity){
			docId = _docId;
			similarity = _similarity;
		}
	};

	bool operator==(const Pair & left, const Pair & right);

	struct ClassComp {
		bool operator() (const Pair & left, const Pair & right) const;
	};

	class ShingleApp :
		public shingleService
	{
	protected:
		void initTextById(unsigned int id, t__text * trgt);
		ClassComp objectcomp;
		DbEnv * env; ///< database in BDB
		Db * hashes, ///< bdb table, contains pairs hash => doc_id
			* docs;	///< bdb table, contains pairs doc_id => documentInfo
		vector<Pair> appResult;
        void findSimilar(t__text & txt);  ///< function compares new text with others already in the base
        ShingleAppLogger * Log;  ///< logger object. Sends messages in several streams
		int shingleAlgorithm(t__text txt, t__result *res); ///< compare two texts using algorithm based on shingles
        int documentCount;///< count of document already stored in base
        int qCount;///< count of querries processed this run
        bool flagContinue;///< setting to false will make application to stop (only after accepting one more connection)
        bool mainEx;///< setting to true will make instance to close DB handlers and free memory allocated for them
    public:
        void stop();///< sets flagContinue to false, stops the application then it accepts one more connection
        void setMain();///< sets mainEx to true, allows application to close DB handlers and free memory allocated for them
        void setChild();///< sets mainEx to false
        virtual int run(int port);
		string nowToStr(); ///< converts current date/time to string
		string ipToStr(); ///< converts current client`s ip to string
        ShingleAppLogger & log();///< getter for Log field
        ShingleApp();
		~ShingleApp();
        virtual	int CompareText(t__text txt, t__result *res);///< main method which process incoming request
	};

	bool txtValid(t__text a);

}
