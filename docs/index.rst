.. MBROLA Delexicaliser documentation master file, created by
   sphinx-quickstart on Fri Aug 28 00:48:05 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to MBROLA Delexicaliser's documentation!
================================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:



Introduction
============

In experimental linguistics and research on speech prosody, it is sometimes useful to construct synthesised speech samples (stimuli) that are delexicalised, i.e. samples where the lexical content is masked and impossible to recognise, and have a specific prosodic profile (duration of segments, pauses, intonation contours etc). In this technical report, we present a software tool that creates delexicalised versions of utterance recordings, based on a time-aligned phonetic transcription. The system, called MBROLA delexicaliser, replaces all phonemes in the transcription with others from the same class of phonemes (respecting the phonotactics rules supplied by the user), copies the segment durations and pitch contours of the original recordings and produces the stimuli by feeding this information to the MBROLA speech synthesiser.

The MBROLA speech synthesiser (Dutoit 1996) is the result of a project initiated by the Faculté Polytechnique de Mons (Belgium), to obtain a set of speech synthesizers for as many voices, languages and dialects as possible, free of use for non-commercial and non-military applications. The MBROLA synthesiser is based on the concatenation of diphones and allows for precise control of segment durations and pitch targets in the output. It is freely available for many computer operating systems. 

This documentation is structured as follows. In Section 2 we will present the Language Definition File, by which the user defines the phonemes of a language, their classes and the constraints in their combinations (phonotactics) that the tool should follow. In Section 3 we will show how to prepare a recording and the associated transcription for use with the tool and in Section 4 we will present the use of the Delexicaliser tool to produce the input files for the MBROLA speech synthesiser. Section 5 describes the example files provided online, Section 6 outlines the perspectives for future development of the tool, and Section 7 contains license information. 




