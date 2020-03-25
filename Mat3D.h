#ifndef __Mat3D_h__
#define __Mat3D_h__

template <class T>
class Mat3D {
private:
    int nn;
    int mm;
    int kk;
    T ***v;
    bool alloc;
public:
    Mat3D();
    Mat3D(int n, int m, int k);
    inline T** operator[](const int i);    //subscripting: pointer to row i
    inline const T* const * operator[](const int i) const;
    inline int dim1() const;
    inline int dim2() const;
    inline int dim3() const;
    ~Mat3D();
    void set(int n, int m, int k, T *a);
};

template <class T>
Mat3D<T>::Mat3D(): nn(0), mm(0), kk(0), v(0), alloc(0) {}

template <class T>
Mat3D<T>::Mat3D(int n, int m, int k) { set(n,m,k); }

template <class T>
void Mat3D<T>::set(int n, int m, int k, T *a=0) 
{
    int i,j;
    nn=n; mm=m; kk=k; alloc=(a==0);
    v = new T**[n];
    v[0] = new T*[n*m];
    v[0][0] = (alloc ? new T[n*m*k] : a);
    for(j=1; j<m; j++)
        v[0][j] = v[0][j-1] + k;
    for(i=1; i<n; i++) {
        v[i] = v[i-1] + m;
        v[i][0] = v[i-1][0] + m*k;
        for(j=1; j<m; j++)
            v[i][j] = v[i][j-1] + k;
    }
}

template <class T>
inline T** Mat3D<T>::operator[](const int i) //subscripting: pointer to row i
{
    return v[i];
}

template <class T>
inline const T* const * Mat3D<T>::operator[](const int i) const
{
    return v[i];
}

template <class T>
inline int Mat3D<T>::dim1() const
{
    return nn;
}

template <class T>
inline int Mat3D<T>::dim2() const
{
    return mm;
}

template <class T>
inline int Mat3D<T>::dim3() const
{
    return kk;
}

template <class T>
Mat3D<T>::~Mat3D()
{
    if (v != 0) {
        if(alloc) delete[] (v[0][0]);
        delete[] (v[0]);
        delete[] (v);
    }
}

typedef const Mat3D<double> Mat3D_I_DP;
typedef Mat3D<double> Mat3D_DP, Mat3D_O_DP, Mat3D_IO_DP;

#endif// __Mat3D_h__