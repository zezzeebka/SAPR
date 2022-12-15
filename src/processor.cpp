#include "processor.h"
#include <vector>
Processor::Processor()
{

}

Processor::Processor(std::shared_ptr<Preprocessor> Preproc)
{
    MainPreproc = Preproc;
}

void Processor::Solve()
{
    std::vector<double> cf;
    std::vector<double> temp = MainPreproc->getConstruction()->getCF();
    cf.push_back(MainPreproc->getConstruction()->getFirstPressure());
    cf.insert(cf.end(), temp.begin(),
              temp.end());

    std::vector<double> d = MainPreproc->getConstruction()->getDF();
    std::vector<double> L = MainPreproc->getConstruction()->getL();
    std::vector<double> A = MainPreproc->getConstruction()->getA();
    std::vector<double> sigma = MainPreproc->getConstruction()->getSigma();
    std::vector<double> E = MainPreproc->getConstruction()->getE();

    std::vector<std::vector<double>> matrixA = std::vector<std::vector<double>>(L.size()+1,
                                                                                std::vector<double>(L.size()+1,0));
    std::vector<double> B = std::vector<double>(matrixA.size(), 0);
    std::vector<double> U = std::vector<double>(B.size(), 0);

    for(int i = 0; i < L.size(); i++)
    {
        double val = A[i]*E[i]/L[i];
        matrixA[i][i]     += val;
        matrixA[i][i+1]   -= val;
        matrixA[i+1][i]   -= val;
        matrixA[i+1][i+1] += val;
    }

    B[0] = cf[0] + (d[0]*L[0])/2;
    B[B.size()-1] = cf[cf.size()-1] + (d[d.size()-1]*L[L.size()-1])/2;
    for( int i = 1; i < L.size(); i++)
    {
        B[i] = cf[i]+ (d[i]*L[i])/2 + (d[i-1]*L[i-1]/2);
    }

    if(MainPreproc->getConstruction()->getLeftSeal())
    {
        matrixA[0][0] = 1;
        matrixA[0][1] = 0;
        matrixA[1][0] = 0;
        B[0] = 0;
    }

    if(MainPreproc->getConstruction()->getRightSeal())
    {
        int n = matrixA.size()-1;
        matrixA[n][n]   = 1;
        matrixA[n-1][n]  = 0;
        matrixA[n][n-1] = 0;
        B[B.size()-1] = 0;

    }

    std::vector<std::vector<double>> T = matrixA;
    int n = T.size();
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::vector<double> f = B;
    a.push_back(0);
    for(int i = 0; i < n; i++){
        c.push_back(T[i][i]);
    }
    for(int i = 0; i < n-1; i++){
        b.push_back(T[i][i+1]);
    }
    for(int i = 1; i < n; i++){
        a.push_back(T[i][i-1]);
    }

    double m;
    for(int i = 1; i < n; i++)
    {
        m = a[i]/c[i-1];
        c[i] = c[i] - m*b[i-1];
        f[i] = f[i] - m*f[i-1];
    }

    U[n-1] = f[n-1]/c[n-1];

    for(int i = n-2; i>=0;i--)
    {
        U[i]=(f[i]-b[i]*U[i+1])/c[i];
    }
    std::cout << "uuuuuuuuuuuuuuuuu";
    for (int i = 0; i < B.size(); i++)
    {
        std::cout << U[i] << ", ";
    }
    std::cout<<std::endl;
}

void Processor::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event)
{

}
