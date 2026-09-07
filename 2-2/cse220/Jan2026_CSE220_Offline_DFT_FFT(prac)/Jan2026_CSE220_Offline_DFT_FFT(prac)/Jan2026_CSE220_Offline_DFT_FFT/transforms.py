"""
transforms.py  --  YOUR CODE GOES HERE.

The shared transform core used by BOTH tasks. Write it once; bigmul.py
(Task A) and image_conv.py (Task B) import it.

Nothing in this file may call numpy.fft, scipy.fft, numpy.convolve,
scipy.signal, or any other library routine that performs a Fourier
transform, a convolution or a correlation for you. NumPy is for array
arithmetic only.

A quick self-test you should run before touching either application:

    import numpy as np
    from transforms import DFTAnalyzer, FFTTransformer
    x = np.random.randn(64) + 1j * np.random.randn(64)
    d, f = DFTAnalyzer(), FFTTransformer()
    assert np.max(np.abs(d.transform(x) - f.transform(x))) < 1e-9
    assert np.max(np.abs(d.inverse(d.transform(x)) - x)) < 1e-9
"""

import numpy as np


def next_power_of_two(n):
    """
    Return the smallest power of two that is >= ``n`` (and at least 1).

    Both tasks need this to choose a transform length for the radix-2 FFT.
    """
    # TODO: implement this function
    i=0
    while (2**i)<n:
        i=i+1
    return 2**i


class DFTAnalyzer:
    """
    The Discrete Fourier Transform, computed straight from its definition.

        Analysis:   X[k] = sum_{n=0}^{N-1} x[n] * exp(-2j*pi*k*n/N)
        Synthesis:  x[n] = (1/N) * sum_{k=0}^{N-1} X[k] * exp(+2j*pi*k*n/N)

    How you write it is up to you -- a literal double loop, a precomputed
    table of twiddle factors indexed by (k*n) % N, or a NumPy expression --
    as long as it computes these sums directly and is not secretly an FFT.
    """

    name = "dft"

    def transform(self, x):
        """
        Forward DFT.

        Parameters
        ----------
        x : 1D array_like, length N (real or complex)

        Returns
        -------
        numpy.ndarray of complex128, shape (N,)
        """
        # TODO: implement this method
        x=np.asarray(x)
        X=np.zeros(len(x),dtype=complex)
        N=len(x)
        for k in range(0,N):
            temp=0
            for n in range(0,N):
                temp+=x[n]*np.exp(-2j*np.pi*k*n/N)
            X[k]= temp
        return X

    def inverse(self, spectrum):
        """
        Inverse DFT, including the 1/N factor.

        Parameters
        ----------
        spectrum : 1D array_like, length N (complex)

        Returns
        -------
        numpy.ndarray of complex128, shape (N,)
            Do NOT discard the imaginary part here -- the caller decides when
            it is safe to take .real.
        """
        # TODO: implement this method
        spectrum=np.asarray(spectrum)
        x=np.zeros(len(spectrum),dtype=complex)
        N=len(spectrum)
        for n in range(0,N):           
            for k in range(N):
                x[n]+=spectrum[k]*np.exp(2j*np.pi*k*n/N)
            x[n]*=1/N 
        return x


class FFTTransformer(DFTAnalyzer):
    """
    Radix-2 decimation-in-time (Cooley-Tukey) FFT, in O(N log N).

    It inherits from DFTAnalyzer so that both applications can treat the two
    interchangeably: they call ``engine.transform(...)`` and
    ``engine.inverse(...)`` without caring which engine they hold.

    Requirements:
      * Recursive or iterative (with bit-reversal permutation) -- your choice.
      * N must be a power of two; raise ValueError for any other length.
        The caller is responsible for zero-padding up to next_power_of_two.
      * The inverse must reuse the same butterfly machinery (conjugated
        twiddles, or conjugate-transform-conjugate), not a second copy of it.
      * Twiddle factors for a stage are computed once per stage, never once
        per butterfly.
    """

    name = "fft"

    def transform(self, x):
        """Forward FFT. Same contract as DFTAnalyzer.transform."""
        # TODO: implement this method
        x = np.asarray(x)
        N = len(x)

        result = np.empty(N, dtype=complex)

        bit = N.bit_length() - 1

        for i in range(N):
            rev = 0
            temp = i

            for j in range(bit):
                rev = (rev << 1) | (temp & 1)
                temp = temp >> 1

            result[rev] = x[i]
            for s in range(1, bit + 1):

                M = 2 ** s
                W_m = np.exp(-2j * np.pi / M)

                # Process every block of size M
                for l in range(0, N - M + 1, M):

                    W = 1

                    # Butterflies inside the block
                    for k in range(M // 2):

                        g = result[l + k]
                        h = W * result[l + k + M // 2]

                        result[l + k] = g + h
                        result[l + k + M // 2] = g - h

                        W = W * W_m

        return result


    def inverse(self, spectrum):
        """Inverse FFT, including the 1/N factor."""
        # TODO: implement this method
        

        spectrum = np.asarray(spectrum)
        N = len(spectrum)

        # FFT requires power-of-two length
        if N < 1 or (N & (N - 1)) != 0:
            raise ValueError("FFT length must be a power of two")

        bits = N.bit_length() - 1

        # Bit reversal
        result = np.empty(N, dtype=complex)

        for i in range(N):
            rev = 0
            temp = i

            for j in range(bits):
                rev = (rev << 1) | (temp & 1)
                temp = temp >> 1

            result[rev] = spectrum[i]

            # Inverse FFT stages
            for s in range(1, bits + 1):

                M = 2 ** s
                W_m = np.exp(2j * np.pi / M)   # PLUS sign

                for l in range(0, N - M + 1, M):

                    W = 1

                    for k in range(M // 2):

                        g = result[l + k]
                        h = W * result[l + k + M // 2]

                        result[l + k] = g + h
                        result[l + k + M // 2] = g - h

                        W = W * W_m

            # 1/N normalization
            result = result / N

        return result


# ---------------------------------------------------------------------------
# BONUS (optional) -- arbitrary-length FFT.
#
# Delete this class if you are not attempting the bonus. If you do attempt it,
# run both tasks with --engine arbitrary and leave those output directories in
# your submission as the evidence.
# ---------------------------------------------------------------------------
class ArbitraryLengthFFT(FFTTransformer):
    """
    Bonus: an O(N log N) transform for ANY length N, not just powers of two.

    Bluestein's chirp-z algorithm is the usual route: rewrite the DFT as a
    convolution of two chirp sequences, and evaluate that convolution with a
    radix-2 FFT of length >= 2N-1. A mixed-radix Cooley-Tukey that factorises
    N is equally acceptable.

    With this engine, Task A no longer has to pad the digit arrays up to a
    power of two, and Task B no longer has to pad the image up to one.
    """

    name = "arbitrary"

    def transform(self, x):
        """Forward DFT for any length using Bluestein's algorithm."""

        x = np.asarray(x, dtype=complex)
        N = len(x)

        if N < 1:
            raise ValueError("Transform length must be at least 1")

        if N == 1:
            return x.copy()

        M = next_power_of_two(2 * N - 1)

        n = np.arange(N)

        chirp = np.exp(-1j * np.pi * (n ** 2) / N)

        a = np.zeros(M, dtype=complex)
        a[:N] = x * chirp

        b = np.zeros(M, dtype=complex)

        b[:N] = np.exp(1j * np.pi * (n ** 2) / N)

        for n_value in range(1, N):
            b[M - n_value] = b[n_value]

        fft = FFTTransformer()

        A = fft.transform(a)
        B = fft.transform(b)

        convolution = fft.inverse(A * B)

        result = convolution[:N] * chirp

        return result

    def inverse(self, spectrum):
        """Inverse arbitrary-length FFT."""

        spectrum = np.asarray(spectrum, dtype=complex)
        N = len(spectrum)

        if N < 1:
            raise ValueError("Transform length must be at least 1")

        result = np.conjugate(
            self.transform(np.conjugate(spectrum))
        ) / N

        return result
