
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

struct Vec3 {
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0)
        : x(x), y(y), z(z) {}
};

float produitScalaire(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float norme(const Vec3& v) {
    return sqrt(produitScalaire(v, v));
}

Vec3 normaliser(const Vec3& v) {
    float n = norme(v);

    if (n == 0)
        return Vec3(0, 0, 0);

    return Vec3(v.x / n, v.y / n, v.z / n);
}

class Lumiere {
public:
    virtual float intensite(const Vec3& position) = 0;

    virtual ~Lumiere() {}
};

class LumiereDirectionnelle : public Lumiere {
private:
    Vec3 direction;
    float couleur;

public:
    LumiereDirectionnelle(Vec3 d, float c)
        : direction(normaliser(d)), couleur(c) {}

    float intensite(const Vec3& position) override {
        // Intensite constante pour une lumiere directionnelle
        return couleur;
    }
};

class LumierePonctuelle : public Lumiere {
private:
    Vec3 positionLumiere;
    float attenuation;

public:
    LumierePonctuelle(Vec3 p, float a)
        : positionLumiere(p), attenuation(a) {}

    float intensite(const Vec3& position) override {
        float dx = position.x - positionLumiere.x;
        float dy = position.y - positionLumiere.y;
        float dz = position.z - positionLumiere.z;

        float distance = sqrt(dx*dx + dy*dy + dz*dz);

        return 1.0f / (1.0f + attenuation * distance * distance);
    }
};

class LumiereSpot : public Lumiere {
private:
    Vec3 positionLumiere;
    Vec3 direction;
    float angleOuverture;

public:
    LumiereSpot(Vec3 p, Vec3 d, float angle)
        : positionLumiere(p),
          direction(normaliser(d)),
          angleOuverture(angle) {}

    float intensite(const Vec3& position) override {
        Vec3 versPoint(
            position.x - positionLumiere.x,
            position.y - positionLumiere.y,
            position.z - positionLumiere.z
        );

        float distance = norme(versPoint);

        if (distance == 0)
            return 1.0f;

        versPoint = normaliser(versPoint);

        float cosAngle = produitScalaire(direction, versPoint);
        float limite = cos(angleOuverture * 3.14159265f / 180.0f);

        if (cosAngle >= limite) {
            return 1.0f / (1.0f + 0.1f * distance * distance);
        }

        return 0.0f;
    }
};

float calculerEclairage(
    const vector<unique_ptr<Lumiere>>& lumieres,
    const Vec3& point
) {
    float total = 0.0f;

    for (const auto& lumiere : lumieres) {
        total += lumiere->intensite(point);
    }

    return total;
}

int main() {
    vector<unique_ptr<Lumiere>> lumieres;

    lumieres.push_back(
        make_unique<LumiereDirectionnelle>(
            Vec3(0, -1, 0), 0.5f
        )
    );

    lumieres.push_back(
        make_unique<LumierePonctuelle>(
            Vec3(0, 0, 0), 0.05f
        )
    );

    lumieres.push_back(
        make_unique<LumiereSpot>(
            Vec3(0, 0, 5), Vec3(0, 0, -1), 30.0f
        )
    );

    Vec3 points[] = {
        Vec3(0, 0, 1),
        Vec3(2, 0, 1),
        Vec3(0, 0, 10)
    };

    for (int i = 0; i < 3; i++) {
        float resultat = calculerEclairage(lumieres, points[i]);

        cout << "Point " << i + 1 << " : ("
             << points[i].x << ", "
             << points[i].y << ", "
             << points[i].z << ")" << endl;

        cout << "Intensite totale = "
             << resultat << endl << endl;
    }

    return 0;
}





