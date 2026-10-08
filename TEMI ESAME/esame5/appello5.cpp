// dati esame

#include "FunzioneVettoriale.h"
#include "gplot++.h"
#include "fmtlib.h"
#include "fstream"
#include "Esperimento.h"
#include "IntegralMC.h"
#include "funzionebase.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1F.h"

using namespace std;
using namespace fmt;

// E' LA MEDIA
double media(vector<double> data)
{
    double media{};

    for (int i = 0; i < ssize(data); i++)
    {
        media += data[i];
    }
    double val = double(media / ssize(data));
    return val;
}

// E' LA VARIANZA
double deviazione(vector<double> data, double media)
{
    double varianza = 0;
    for (int k = 0; k < data.size(); k++)
    {
        varianza += (data[k] - media) * (data[k] - media);
    }

    varianza = double(varianza / (data.size() - 1.0));
    return (varianza);
}

double correlazione(vector<double> a, vector<double> b, vector<double> ab)
{
    return (media(ab) - media(a) * media(b)) / sqrt((deviazione(a, media(a)) * deviazione(b, media(b))));
}

int main(int argc, char *argv[])
{
    cout << endl
         << "PUNTO 1" << endl;
    ScaricaCondensatore experiment(1);

    const int n_cicli{10000};

    Gnuplot distribuzioni_cap{};

    distribuzioni_cap.redirect_to_png("Output/Distribuzioni_Cap.png", "1000, 1000");
    vector<double> Cap{};
    vector<double> tempi{}, Resistenza{}, volt0{}, volt1{};
    vector<double> Ctempi{}, CResistenza{}, CVolt0{}, CVolt1{};

    for (int i = 0; i < n_cicli; i++)
    {
        experiment.esegui();
        experiment.analizza();
        Cap.push_back(experiment.get_C_casuale());
        tempi.push_back(experiment.get_T());
        Resistenza.push_back(experiment.get_r());
        volt0.push_back(experiment.get_V_0());
        volt1.push_back(experiment.get_V_1());
        Ctempi.push_back(experiment.getCT());
        CResistenza.push_back(experiment.getCR());
        CVolt0.push_back(experiment.getCV0());
        CVolt1.push_back(experiment.getCV1());
    }

    double average = media(Cap);
    double dev_std = sqrt(deviazione(Cap, average));

    distribuzioni_cap.histogram(Cap, 50);
    distribuzioni_cap.set_yrange(0, NAN);
    distribuzioni_cap.show();
    double err_percentuale = dev_std / average;
    fmt::println("Istogramma salvato in Output/Distribuzioni_DeltaT.png");
    fmt::println("Media = {:4f} metri+-  deviazione = {:4f} metri", average*1000000, dev_std*1000000);
    fmt::println("Errore percentuale = {:4f}%", err_percentuale * 100);

    cout << endl
         << "PUNTO 2" << endl;
    // USO LA CORRELAZIONE
    Gnuplot corr{};
    corr.redirect_to_png("Output/Correlazioni.png", "1600, 1600");
    corr.multiplot(2, 2);

    corr.set_title("Correlazione Capacità - Tempi");
    corr.plot(Cap, tempi, "", Gnuplot::LineStyle::POINTS);
    corr.set_xlabel("Capacità");
    corr.show();

    corr.set_title("Correlazione Capacità - Resistenza");
    corr.plot(Cap, Resistenza, "", Gnuplot::LineStyle::POINTS);
    corr.set_xlabel("Capacità");
    corr.show();

    corr.set_title("Correlazione Capacità - Volt0");
    corr.plot(Cap, volt0, "", Gnuplot::LineStyle::POINTS);
    corr.set_xlabel("Capacità");
    corr.show();

    corr.set_title("Correlazione Capacità - Volt1");
    corr.plot(Cap, volt1, "", Gnuplot::LineStyle::POINTS);
    corr.set_xlabel("Capacità");
    corr.set_xlabel("Capacità");

    corr.show();

    fmt::println("Correlazione tra tempi e capacità = {}", correlazione(tempi, Cap, Ctempi));
    fmt::println("Correlazione tra Resistenze e capacità = {}", correlazione(Resistenza, Cap, CResistenza));
    fmt::println("Correlazione tra V0 e capacità = {}", correlazione(volt0, Cap, CVolt0));
    fmt::println("Correlazione tra V1 e capacità = = {}", correlazione(volt1, Cap, CVolt1));

    fmt::println("La correlazione tra tempi e capacità ( = {}) è il fattore che influisce maggiormente sull'errore sulla Capacità", correlazione(tempi, Cap, Ctempi));

    cout << endl
         << "PUNTO 3" << endl;
    Gnuplot errori{};
    errori.redirect_to_png("Output/Grafico_Errori_C_AlVariarediErrori_su_V.png", "1000,1000");
    vector<double> std_dev{};
    vector<double> err_V{};
    for (double err = 0.02; err <= 0.07; err += 0.001)
    {
        Cap.clear();
        experiment.setErrV(err);
        for (int i = 0; i < n_cicli; i++)
        {
            experiment.esegui();
            experiment.analizza();
            Cap.push_back(experiment.get_C_casuale());
        }
        average = media(Cap);
        std_dev.push_back(sqrt(deviazione(Cap, average)) / average);
        err_V.push_back(err);
    }
    errori.plot(err_V, std_dev);
    errori.set_xlabel("Errori su V");
    errori.set_ylabel("Errori su C");
    errori.set_title("Errori su Capacità al variare degli errori degli errori sulla misura del Potenziale");
    errori.show();
    fmt::println("Plot salvato in Output/Grafico_Errori_C_AlVariarediErrori_su_V.png");

    // svolto fit per il punto 4
    cout << endl
         << "PUNTO 4" << endl;
    TGraphErrors mygraph;

    for (int k = 0; k < err_V.size(); ++k)
    {
        mygraph.SetPoint(k, err_V[k], std_dev[k]);
    }
    TF1 *myfun = new TF1("fitfun", "[0]*x+[1]", err_V.front(), err_V.back());
    mygraph.Fit(myfun);

    double q = myfun->GetParameter(1);
    double m = myfun->GetParameter(0);

    double errore07 = (0.07 - q) / m;

    fmt::println("Errore su V necessario per avere un errore di 7% = {:4f}%", errore07*100);

    return 0;
}