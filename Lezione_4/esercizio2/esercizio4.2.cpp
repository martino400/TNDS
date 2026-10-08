#include "TApplication.h"
#include "TAxis.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "funzioni.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    cout << ("------------------------------------------------ E/m.cpp ------------------------------------------------------------------------") << endl;
    vector<double> v, rB, erroriV, erroriB;
    ParseFile("eom.dat", v, rB, erroriV, erroriB);
    TApplication app{"app", 0, 0};
    TCanvas can1{};
    can1.cd();
    // Questo serve per far vedere come sono distribuite le cariche
    TH1F histo{"cariche", "Distribuzione di DeltaV", 20, 290, 600};
    for (int i{}; i < ssize(v); i++)
    {
        cout << v[i] << " " << rB[i] << " " << erroriV[i] << " " << erroriB[i] << endl;
        // out << v[i] << " " << rB[i] << " " << erroriV[i] << " " << erroriV[i] << endl;
        histo.Fill(v[i]);
    }
    histo.Draw();
    histo.GetXaxis()->SetTitle("Charge [C]");
    can1.SaveAs("Immagini/DistribuzioneDeltaV.png");

    TGraphErrors mygraph;
    for (size_t k = 0; k < v.size(); ++k)
    {
        mygraph.SetPoint(k, v[k], rB[k]);
        mygraph.SetPointError(k, erroriV[k], erroriB[k]);
    }

    TF1 *myfun = new TF1("fitfun", "[0]*x+[1]", v.front(), v.back());
    mygraph.Fit(myfun);

    double moe = myfun->GetParameter(0);
    double error = abs(1. / moe) * myfun->GetParError(0) / abs(moe);

    cout << "Valore di e/m dal fit = " << 1. / moe << "  +/-  " << error << endl;
    cout << "Valore del chi2 del fit = " << myfun->GetChisquare() << endl;
    cout << "          prob del chi2 = " << myfun->GetProb() << endl;
    cout << "Valore del chi2 ridotto = " << myfun->GetChisquare() / (v.size() - 2) << endl;

    ofstream out("results.txt");
    if (out.is_open())
    {
        out << "Valore di e/m dal fit = " << 1. / moe << "  +/-  " << error << endl;
        out << "Valore del chi2 del fit = " << myfun->GetChisquare() << endl;
        out << "          prob del chi2 = " << myfun->GetProb() << endl;
        out << "Valore del chi2 ridotto = " << myfun->GetChisquare() / (v.size() - 2) << endl;
    }
    else
    {
        cerr << "Errore nell'apertura del file di output" << endl;
    }
    // TGraphErrors mygraph = DoPlot(rB, v, erroriB);
    // TF1 *miafunzione = new TF1("fitfunzione", "[0]*x+[1]", 0, 3e-10);
    // mygraph.Fit(miafunzione);
    // double moe = miafunzione->GetParameter(0);
    // cout << "Valore di e/m dal fit = " << moe << "+/-" << endl;//error << endl;
    // cout << "Valore del chi2 del fit = " << miafunzione->GetChisquare() << endl;
    // cout << "          prob del chi2 = " << miafunzione->GetProb() << endl;

    TCanvas trend("trend", "Trend e/m", 800, 600);
    mygraph.Draw("AP.");
    mygraph.SetMarkerStyle(20);
    mygraph.SetMarkerSize(0.5);
    mygraph.SetTitle("Misura e/m");
    mygraph.GetXaxis()->SetTitle("2#DeltaV (V)");
    mygraph.GetYaxis()->SetTitle("(B_{z}R)^{2} (T^{2}m^{2} )");

    TLegend leg(0.15, 0.7, 0.3, 0.85);
    leg.AddEntry(&mygraph, "data", "p");
    leg.AddEntry(myfun, "fit", "l");
    leg.Draw("same");

    trend.Update();
    trend.SaveAs("Immagini/Fit_e_m.png");
    out.close();

    app.Run();
}
