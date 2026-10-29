
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cctype>

using namespace std;

class Plugin {
public:
    virtual string nom() const = 0;

    virtual string traiter(const string& texte) = 0;

    virtual ~Plugin() {}

    static unique_ptr<Plugin> creerPlugin(const string& type);
};

class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override {
        return "Correcteur orthographique";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        size_t position = 0;

        while ((position = resultat.find(" bonjourr", position))
                != string::npos) {
            resultat.replace(position, 9, " bonjour");
            position += 8;
        }

        position = 0;

        while ((position = resultat.find(" language", position))
                != string::npos) {
            resultat.replace(position, 9, " langage");
            position += 8;
        }

        return resultat;
    }
};

class TraducteurAnglais : public Plugin {
public:
    string nom() const override {
        return "Traducteur anglais";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        vector<pair<string, string>> mots = {
            {"bonjour", "hello"},
            {"maison", "house"},
            {"chat", "cat"},
            {"livre", "book"}
        };

        for (const auto& mot : mots) {
            size_t position = 0;

            while ((position = resultat.find(mot.first, position))
                    != string::npos) {
                resultat.replace(
                    position, mot.first.length(), mot.second
                );

                position += mot.second.length();
            }
        }

        return resultat;
    }
};

class AnalyseurStyle : public Plugin {
public:
    string nom() const override {
        return "Analyseur de style";
    }

    string traiter(const string& texte) override {
        string resultat = texte;
        int nombrePhrasesLongues = 0;
        int longueurPhrase = 0;

        for (char caractere : texte) {
            if (caractere == '.' || caractere == '!' ||
                caractere == '?') {

                if (longueurPhrase > 50) {
                    nombrePhrasesLongues++;
                }

                longueurPhrase = 0;
            } else {
                longueurPhrase++;
            }
        }

        if (longueurPhrase > 50) {
            nombrePhrasesLongues++;
        }

        resultat += "\n[Analyse de style] ";

        if (nombrePhrasesLongues > 0) {
            resultat += "Attention : ";
            resultat += to_string(nombrePhrasesLongues);
            resultat += " phrase(s) trop longue(s).";
        } else {
            resultat += "Aucune phrase trop longue detectee.";
        }

        return resultat;
    }
};

unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") {
        return make_unique<CorrecteurOrthographique>();
    }
    else if (type == "traducteur") {
        return make_unique<TraducteurAnglais>();
    }
    else if (type == "analyseur") {
        return make_unique<AnalyseurStyle>();
    }

    return nullptr;
}

int main() {
    vector<unique_ptr<Plugin>> plugins;

    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("analyseur"));

    string texte;

    cout << "Entrez votre texte : ";
    getline(cin, texte);

    for (const auto& plugin : plugins) {
        if (plugin != nullptr) {
            texte = plugin->traiter(texte);

            cout << "\nPlugin applique : "
                 << plugin->nom() << endl;

            cout << "Texte obtenu : " << endl;
            cout << texte << endl;
        }
    }

    return 0;
}





