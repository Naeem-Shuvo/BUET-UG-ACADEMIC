import numpy as np
from transforms import DFTAnalyzer, FFTTransformer, next_power_of_two
def transform_2d(plane, engine):
    """
    2D forward transform of a single 2D array, by separability.

    The 2D DFT factorises into 1D transforms: transform every ROW, then
    transform every COLUMN of the result (the order does not matter). This is
    the only reason a 2D transform is affordable -- doing it directly from the
    2D definition would be O(N^4).

    Parameters
    ----------
    plane : 2D array_like, shape (P, Q)
    engine : DFTAnalyzer or FFTTransformer

    Returns
    -------
    numpy.ndarray of complex128, shape (P, Q)
    """
    plane=np.asarray(plane)
    row,col=np.shape
    result=np.asarray(plane,dtype=complex).copy()
    for r in range(row):
        result[r,:]=engine.transform(result[r,:])
    for c in range(col):
        result[:,c]=engine.transform(result[:,c])
    return result

