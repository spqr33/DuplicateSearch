#include "FileSystemTraverser.h"
#include "AbstractHash.h"
#include "DuplicatesHolder.h"
#include "ErrorHolder.h"
#include <memory>
#include <string>
#include <sys/stat.h>
#include <errno.h>
#include <iostream>
#include <boost/program_options.hpp>
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>

namespace po = boost::program_options;

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::shared_ptr;
using namespace LobKo;


/**
 * 
 */
int main(int argc, char** argv) {
    //testSerialization();
    string progName(*argv);
    string searchPath;
    string label;
    string saveDuplicatesToThisFile;

    
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("search-path,p", po::value<string>(&searchPath), "Start finding here")
            ("label,l", po::value<string>(&label), "Set label")
            ("save-duplicates-to,s", po::value<string>(&saveDuplicatesToThisFile), "Path to result XML file.");
           
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if ( vm.count("help") ) {
        cerr << desc << "\n";

        return EXIT_FAILURE;
    }

    if ( !vm.count("search-path") ) {
        cout << "Please, specify path for traversing" << endl;
        cout << desc << "\n";

        return EXIT_FAILURE;
    }

    if ( !vm.count("label") ) {
        cout << "Please, set a label" << endl;
        cout << desc << "\n";

        return EXIT_FAILURE;
    }

    if ( !vm.count("save-duplicates-to") ) {
        cerr << "Please, specify filename to save results" << endl;
        cout << desc << "\n";

        return EXIT_FAILURE;
    }

    shared_ptr<struct stat> spStatBuf(new struct stat);
    if ( lstat(searchPath.c_str(), spStatBuf.get()) < 0 ) {
        cout << progName << ": " << strerror(errno) << endl;

        return EXIT_FAILURE;
    }

    std::ofstream outputDuplicatesFile(saveDuplicatesToThisFile.c_str());
    if ( !outputDuplicatesFile.is_open() ) {
        cerr << "Can't open the file " << saveDuplicatesToThisFile << " for writting" << endl;

        exit(EXIT_FAILURE);
    }

    shared_ptr<ErrorsHolder> spErrorsHolder(new ErrorsHolder());
    FileSystemTraverser::Result traverseResult;
    FileSystemTraverser traverser(searchPath, label, spErrorsHolder);
    shared_ptr<MetaDataFilesHolder> sMetaDataFilesHolder = traverser.traverse(traverseResult);

    if ( traverseResult == FileSystemTraverser::Result::ERR ) {
        cout << "An error occurred while traversing. Check ErrorHolder." << endl;
    }
    sMetaDataFilesHolder->sort(CompareBySize());

    shared_ptr<SameSizeFileHolder> spSameSizeFileHolder = sMetaDataFilesHolder->getSameSizes();
    shared_ptr<DuplicatesHolder> spDuplicatesHolder = spSameSizeFileHolder->getDuplicates(AbstractHash::Algo::MD5);

    //PrintDuplicatesHolder(*spDuplicatesHolder);

    boost::archive::xml_oarchive _archive(outputDuplicatesFile);
    _archive << BOOST_SERIALIZATION_NVP(spDuplicatesHolder);

    outputDuplicatesFile.clear();
    outputDuplicatesFile.close();
    return EXIT_SUCCESS;
}
