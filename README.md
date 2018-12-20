# PersichettiOTScryptanalysis
Cryptanalysis of Persichetti's One-Time Signature (OTS) from quasi-cyclic codes

This repository hosts the implementation of the cryptanalysis of the OTS proposed by Persichetti in [ePrint 2017/397](https://eprint.iacr.org/2017/397). Full details are available in [ePrint 2018/1205](https://eprint.iacr.org/2018/1205).

## Compilation

This piece of software should compile on Linux systems using the traditional `make` command. It will produce an executable file `breakOTS`.

## Usage

To run this piece of software, use:
```
./breakOTS p w1 w2 delta relax sigFile threshold maxBFround
```

Where the parameters should be:
1. `p` the length of the code,
1. `w1` the hamming weight of the secret key,
1. `w2` the hamming weight of the one-time randomness used for signing,
1. `delta` the hamming weight of the commitment,
1. `relax` a relaxation parameter that helps the cryptanalysis (see Sec. 6 of [ePrint 2018/1205](https://eprint.iacr.org/2018/1205)),
1. `sigFile` the path to the file containing the signature (see below for formatting),
1. `threshold` a tuning parameter for the extended bit flipping algorithm (see Tab. 1 of [ePrint 2018/1205](https://eprint.iacr.org/2018/1205)),
1. `maxBFround` an upper bound on the number of execution rounds for the extended bit flipping algorithm.

## Algorithm output

The program outputs (in `stdout`) the candidate secret key *x0* and *x1* as well as some information about the inputs and the execution time.

## Expected format of the signature

Recall that a OTS in Persichetti's scheme corresponds to a couple (*c*, *z*), with *z* = (*z0*, *z1*).
The signature file is expected to have the following format:
```
[... c  ...]\n
[... z0 ...]\n
[... z1 ...]\n
```
For instance, if p=5, *c* = [0 1 0 1 0], and *z* = (*z0*, *z1*) = ([1 1 0 0 0], [0 0 0 1 1]), then `sigFile` is expected to contain:
```
[0 1 0 1 0]\n
[1 1 0 0 0]\n
[0 0 0 1 1]\n
```

## Sample files

We provide 4 samples of signature files, one for each set of parameters (see Tab. 2 of [ePrint 2017/397](https://eprint.iacr.org/2017/397)), obtained using a homemade (dirty) implementation of Persichetti's OTS.

`samples/set-i.txt` contains a one-time signature using parameters of the *i*-th line of Tab. 2. For instance, in `sample/set-2.txt`, we have p=9857.


## Reporting bugs, comments

Please feel free to report any problem encountered by mail (jean-christophe[dot]deneuville[at]insa-cvl[dot]fr) or using the issues feature.
