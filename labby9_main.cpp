#include "Rsa_assign.h"
#include<iostream>



int main() {
    // n < 90909090990
    const int64 p = 9967;
    const int64 q = 9973;
    const int64 n = p * q; // n = 99400891
    const int64 phi = (p - 1) * (q - 1);




    const int64 e = 65537;
    //e must be coprime to ohi

    //verify gcd

    if (gcd(e, phi) != 1) {
        cout << "Debug:: E isnt relative prime to phi" << endl;
        return 1;

    }

    int64 d = extendGCD(e, phi);


    //calc private key
    cout << "Rsa config: " << endl;
    cout << "p: " << p << ", q: " << q << endl;
    cout << "n: " << n << endl;
    cout << "e (Public): " << e << endl;
    cout << "d (Private): " << d << endl;
    cout << "-----------------------------------" << endl;




    string originalMsg = "The camera is hidden in the bushes";
    string cleanMsg = "";



    for (char c : originalMsg) {
        if (c != ' ') {
            cleanMsg += toupper(c);
        }
    }


    while (cleanMsg.length() % 4 != 0) {
        cleanMsg += 'X';
    }

    cout << "Pre Proccesed message:" << cleanMsg << endl;



    //encryption
    ofstream outFile("encrypt.rsa");

    if (!outFile.is_open()) {
        cout << "Debug:: ~encryption~ file didnt open" << endl;
        return 1;
    }

    cout << "encrypting" << endl;





    for (size_t i = 0; i < cleanMsg.length(); i += 4) {
        int64 M = (int64)cleanMsg[i] * 1000000 +
            (int64)cleanMsg[i + 1] * 10000 +
            (int64)cleanMsg[i + 2] * 100 +
            (int64)cleanMsg[i + 3];



        int64 C = modPow(M, e, n);

        outFile << C << " ";



    }
    outFile.close();
    cout << "Encrypion complete. Look at encrypt.rsa" << endl;








    // decrypt
    ifstream inFile("encrypt.rsa");
    ofstream decryptFile("decrypt.rsa");

    if (!inFile.is_open() || !decryptFile.is_open()) {
        cout << "Debug:: ~decrypt~ file isnt open" << endl;
        return 1;
    }

    string TrueMessage = "";
    int64 encryptedBlock;

    cout << "Deccrypting" << endl;

    while (inFile >> encryptedBlock) {
        int64 M = modPow(encryptedBlock, d, n); // decrypt


        // Decode back to chars
        char c1 = (M / 1000000) % 100;
        char c2 = (M / 10000) % 100;
        char c3 = (M / 100) % 100;
        char c4 = M % 100;

        TrueMessage += c1;
        TrueMessage += c2;
        TrueMessage += c3;
        TrueMessage += c4;


    }


    //end


    decryptFile << TrueMessage;

    inFile.close();
    decryptFile.close(); // i LOVE forgetting the semicolon before the end


    cout << "Debug:: /end/    decrypting done, look at decrypt.rsa " << endl;
    cout << "The message was " << TrueMessage << endl;
    



    return 0;
}