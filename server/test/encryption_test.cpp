#include <iostream>
#include <string>
#include <vector>

int encodeToASCII(const std::string& input) {
    int encodedValue = 0;
    
    for (char c : input) {
        encodedValue = (encodedValue * 1000) + static_cast<int>(c);
    }
    
    return encodedValue;
}

std::string decodeFromASCII(int encodedValue) {
    std::string decodedString;
    
    while (encodedValue > 0) {
        int asciiValue = encodedValue % 1000;
        decodedString = static_cast<char>(asciiValue) + decodedString;
        encodedValue /= 1000;
    }
    
    return decodedString;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> names = {"Ava", "Bea", "Cay", "Dan", "Eva", "Fay", "Gia", "Hal", "Ida", "Jay",
                                 "Kai", "Leo", "Mae", "Nia", "Ora", "Pia", "Qua", "Rae", "Sky", "Taj",
                                 "Uma", "Van", "Wyn", "Xia", "Yen", "Zia", "No", "Stormzy"};
    
    int testsPassed = 0;
    for (int i = 0; i < names.size(); i++) {
        std::string name = decodeFromASCII(encodeToASCII(names[i]));
        if (names[i] == name) {
            testsPassed++;
        }
        else {
            std::cout << "FAILED: " << name << " (expected: " << names[i] << ")" << std::endl;
        }
    }

    std::cout << "Passed " <<testsPassed << " out of " << names.size() << " tests." << std::endl;
    std::cout << encodeToASCII("Kay");
    return 0;
}