#include <iostream>

class IEngine {
public:
    virtual void StartEngine() = 0;
    virtual void StopEngine() = 0;
};

class IRadio {
    public:
    virtual void TurnOnRadio() = 0;
    virtual void SetFrequency(double freq) = 0;
};

class IGPS {
    public:
    virtual void StartNavigation() = 0;
};
class EngineUnit : public IEngine {
public:
    void StartEngine() override {
        std::cout << "Engine started\n";
    }

    void StopEngine() override {
        std::cout << "Engine stopped\n";
    }
};

class RadioTuner : public IRadio {
public:


    void TurnOnRadio() override {
        std::cout << "Radio on\n";
    }

    void SetFrequency(double freq) override {
        std::cout << "Radio frequency set to " << freq << "\n";
    }
};

class GPSModule : public IGPS {
public:
    void StartNavigation() override {
        std::cout << "Navigation started\n";
    }
};

class CarComputer {
private:
    IEngine* engine;
    IRadio* radio;
    IGPS* gps;

public:
public:
    CarComputer(IEngine* e, IRadio* r, IGPS* g)
        : engine(e), radio(r), gps(g) {}

    void StartCar() {
        engine->StartEngine();
    }

    void PlayMusic() {
        radio->TurnOnRadio();
        radio->SetFrequency(101.5);
    }

    void Navigate() {
        gps->StartNavigation();
    }
};

int main() {
    EngineUnit engine;
    RadioTuner radio;
    GPSModule gps;

    CarComputer car(&engine, &radio, &gps);

    car.StartCar();
    car.PlayMusic();
    car.Navigate();

    return 0;
}
