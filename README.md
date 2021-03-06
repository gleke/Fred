# Fred ![alt text](https://raw.githubusercontent.com/derohde/Fred/master/logo/logo.png "Fred logo")
A fast, scalable and light-weight C++ Fréchet distance library, exposed to python.

## Ingredients C++ Backend
`import Fred.backend as fred`

- continous Fréchet distance
  - signature: `fred.continuous_frechet(curve1, curve2, approximation_error, round)` approximation_error defaults to 0.001 and round (rounding up to 3 decimals) defaults to true
  - returns: `fred.Continuous_Frechet_Result` with members `value`, `time_bounds`: running-time for upper and lower bound, `number_searches`: number of free space diagrams built, `time_searches`: running-time for free spaces
- discrete Fréchet distance
  - signature: `fred.discrete_frechet(curve1, curve2)`
  - returns: `fred.Discrete_Frechet_Result` with members `value` and `time`
- discrete k-center clustering (continuous Fréchet) [Without simplification; from **Approximating (k,l)-center clustering for curves**](https://dl.acm.org/doi/10.5555/3310435.3310616)
  - signature: `fred.discrete_kcenter(k, curves, approximation_error, round, with_assignment)` with parameters `approximation_error`, `round`: see continuous Fréchet, `with_assignment`: defaults to false; assigns curves to nearest centers if true
  - returns: `fred.Clustering_Result` with mebers `value`: objective value, `time`, `assignment`: empty if with_assignment=false
- discrete k-median clustering (continuous Fréchet) [Algorithm 6 in **Coresets for (k,l)-Clustering under the Fréchet distance**](https://arxiv.org/pdf/1901.01870.pdf)
  - signature: `fred.discrete_kmedian(k, curves, approximation_error, with_assignment)` with parameters `approximation_error`, `round`: see continuous Fréchet, `with_assignment`: defaults to false; assigns curves to nearest centers if true
  - returns: `fred.Clustering_Result` with mebers `value`: objective value, `time`, `assignment`: empty if with_assignment=false
- discrete one-median clustering (continuous Fréchet) via sampling [Section 3 in **Random Projections and Sampling Algorithms for Clustering of High Dimensional Polygonal Curves**](https://papers.nips.cc/paper/9443-random-projections-and-sampling-algorithms-for-clustering-of-high-dimensional-polygonal-curves)
  - signature: `fred.discrete_onemedian_sampling(curves, epsilon_sampling, approximation_error, with_assignment)` with parameters `approximation_error`, `round`: see continuous Fréchet, `epsilon_sampling`: (1+epsilon) approximation parameter, `with_assignment`: defaults to false; assigns curves to nearest centers if true
  - returns: `fred.Clustering_Result` with mebers `value`: objective value, `time`, `assignment`: empty if with_assignment=false
- dimension reduction via. gaussian random projection [Section 2 in **Random Projections and Sampling Algorithms for Clustering of High Dimensional Polygonal Curves**](https://papers.nips.cc/paper/9443-random-projections-and-sampling-algorithms-for-clustering-of-high-dimensional-polygonal-curves)
  - signature: `fred.dimension_reduction(curves, epsilon, empirical_constant)` with parameters `epsilon`: (1+epsilon) approximation parameter, `empirical_constant`: use constant of empirical study (faster, but less accurate)
  - returns: `fred.Curves` collection of curves
  
### Mini Example
```python
import Fred.backend as fred
import numpy as np
import pandas as pd

curve1d = fred.Curve(np.array([1., 2.])) # Curve stores a polygonal curve with 
                                         # at least two points of at least one 
                                         # and equal number of dimensions

curve2d1 = fred.Curve(np.array([[1., 0.], [2., 0.], [3., 0.]])) # any number of dimensions and points works
curve2d2 = fred.Curve(np.array([[1., -1.], [2., -1.], [3., -1.]])) 

print(curve2d1)

print("distance is {}".format(fred.continuous_frechet(curve2d1, curve2d2).value))


import requests, zipfile, io             # you can use all libraries 
                                         # that work with numpy to read data into fred
                                         
re = requests.get("https://archive.ics.uci.edu/ml/machine-learning-databases/00447/data.zip", stream=True)
zf = zipfile.ZipFile(io.BytesIO(re.content))

ps1 = fred.Curve(pd.read_csv(zf.open('PS1.txt'), delimiter="\t", header=None).values)
ps2 = fred.Curve(pd.read_csv(zf.open('PS2.txt'), delimiter="\t", header=None).values)
ps3 = fred.Curve(pd.read_csv(zf.open('PS3.txt'), delimiter="\t", header=None).values)
ps4 = fred.Curve(pd.read_csv(zf.open('PS4.txt'), delimiter="\t", header=None).values)
ps5 = fred.Curve(pd.read_csv(zf.open('PS5.txt'), delimiter="\t", header=None).values)
ps6 = fred.Curve(pd.read_csv(zf.open('PS6.txt'), delimiter="\t", header=None).values)

curves = fred.Curves() # for clustering or if you want to apply dimension reduction
                       # you need to encapsulate your curves in a Curves object
              
curves.add(ps1)
curves.add(ps2)
curves.add(ps3)
curves.add(ps4)
curves.add(ps5)
curves.add(ps6)

curves = fred.dimension_reduction(curves, 0.95) # fred is pretty fast but with high dimensional data
                                                # a dimension reduction massively improves running time
                                                # even for smaller values of epsilon
                                  
                                               
clustering = fred.discrete_kmedian(2, curves)

print("clustering cost is {}".format(clustering.value))

for i, center in enumerate(clustering):
    print("center {} is {}".format(i, curves[center]))
```
  
## Installation
Get requirements under Ubuntu: `make pre`

Python3 installation into userdir: `make python3`

Python2 installation into userdir: `make python2`

## Test
Just run `python py/test.py`.
