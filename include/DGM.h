#pragma once

#include "../DGM/CMat.h"
#include "../DGM/NDGauss.h"
#include "../DGM/SamplesAccumulator.h"
#include "../DGM/Random.h"

#include "../DGM/PDF.h"
#include "../DGM/PDFHistogram.h"
#include "../DGM/PDFGaussian.h"

#include "../DGM/FeaturesConcatenator.h"

#include "../DGM/Marker.h"
#include "../DGM/MarkerHistogram.h"
#include "../DGM/MarkerGraph.h"

#include "../DGM/Prior.h"
#include "../DGM/PriorNode.h"
#include "../DGM/PriorEdge.h"
#include "../DGM/PriorTriplet.h"

#include "../DGM/Train.h"
#include "../DGM/TrainNode.h"
#include "../DGM/TrainNodeNaiveBayes.h"
#include "../DGM/TrainNodeGM.h"
#include "../DGM/TrainNodeGMM.h"
#include "../DGM/TrainNodeCvGMM.h"
#include "../DGM/TrainNodeCvGM.h"
#include "../DGM/TrainNodeCvRF.h"
#include "../DGM/TrainNodeMsRF.h"
#include "../DGM/TrainEdge.h"
#include "../DGM/TrainEdgePotts.h"
#include "../DGM/TrainEdgePottsCS.h"
#include "../DGM/TrainEdgePrior.h"
#include "../DGM/TrainEdgeConcat.h"
#include "../DGM/TrainTriplet.h"
#include "../DGM/TrainLink.h"
#include "../DGM/TrainLinkNested.h"

#include "../DGM/Graph.h"
#include "../DGM/GraphExt.h"
#include "../DGM/Graph3.h"

#include "../DGM/Infer.h"
#include "../DGM/InferExact.h"
#include "../DGM/InferChain.h"
#include "../DGM/InferTree.h"
#include "../DGM/InferLBP.h"
#include "../DGM/InferViterbi.h"

#include "../DGM/Decode.h"
#include "../DGM/DecodeExact.h"
#include "../DGM/DecodeTRW.h"

#include "../DGM/Powell.h"

/**
@mainpage Introduction
@section sec_main Direct Graphical Models (DGM)
is a C++ dynamic link library implementing various tasks in <a href="https://en.wikipedia.org/wiki/Graphical_model">probabilistic graphical models</a> with pairwise dependencies. 
The library aims to be used for the <a href="https://en.wikipedia.org/wiki/Markov_random_field">Markov-</a> and 
<a href="https://en.wikipedia.org/wiki/Conditional_random_field">Conditional Random Fields</a> (MRF / CRF), 
<a href="https://en.wikipedia.org/wiki/Markov_chain">Markov Chains</a>, <a href="https://en.wikipedia.org/?title=Bayesian_network">Bayesian Networks</a>, @a etc. 
DGM library consists of two modules: 
- Main @ref moduleDGM, which includes a variety of methods for the tasks:
	- @ref moduleTrain
	- @ref moduleGraph
	- @ref moduleDecode
	- @ref moduleParamEst
	- @ref moduleVis
- Feature extraction @ref moduleFEX, which allows for extracting the main data features, used nowadays in image classification.

These tasks are optimized for speed, @a i.e. high-efficient calculations. The code is written entirely in C++ and can be compiled with Microsoft Visual C++.

@section sec_main_overview Methods Overview
@subsection sec_main_train Training
DGM implements the following training methods: 

@subsubsection sec_main_train_nodes Nodes | Unary Potentials
- <b>NaiveBayes:</b> Naive Bayes training @ref DirectGraphicalModels::CTrainNodeNaiveBayes
- <b>GM:</b> Gaussian Model training @ref DirectGraphicalModels::CTrainNodeGM
- <b>CvGM:</b> OpenCV Gaussian Model training @ref DirectGraphicalModels::CTrainNodeCvGM
- <b>GMM:</b> Gaussian Mixture Model training (<a href="http://www.project-10.de/Kosov/files/GCPR_2013.pdf" target="_blank">Sequential GMM Training Algorithm</a>) @ref DirectGraphicalModels::CTrainNodeGMM
- <b>CvGMM:</b> OpenCV Gaussian Mixture Model training @ref DirectGraphicalModels::CTrainNodeCvGMM
- <b>CvRF:</b> OpenCV Random Forest training @ref DirectGraphicalModels::CTrainNodeCvRF
- <b>MsRF:</b> Microsoft Research Random Forest training @ref DirectGraphicalModels::CTrainNodeMsRF

The corresponding classes are @b CTrainNode* (where @b * is the name of the method above). The difference between these methods is described at forum:
<a href="http://www.project-10.de/forum/viewtopic.php?f=22&t=954">Training of a Random Model</a>.

@subsubsection sec_main_train_edges Edges | Pairwise Potentials
- <b>Potts:</b> Train- & Test-data-independent Potts model @ref DirectGraphicalModels::CTrainEdgePotts
- <b>PottsCS:</b> Train-data-independent contrast-sensitive Potts model @ref DirectGraphicalModels::CTrainEdgePottsCS
- <b>Prior:</b> Contrast-sensitive Potts model with prior probability @ref DirectGraphicalModels::CTrainEdgePrior
- <b>Concat:</b> Concatenated training @ref DirectGraphicalModels::CTrainEdgeConcat

The corresponding classes are @b CTrainEdge* (where @b * is the name of the method above).

@subsection sec_main_decode Inference / Decode
DGM implements the following inference and decoding methods: 

@subsubsection sec_main_decode_inference Inference
- <b>Exact:</b> Exact inferece for small graphs with an exhaustive search @ref DirectGraphicalModels::CInferExact
- <b>Chain:</b> Exact inferece for Markov chains (chain-structured graphs) @ref DirectGraphicalModels::CInferChain
- <b>Tree:</b> Exact inferece for undirected graphs without loops (tree-structured graphs) @ref DirectGraphicalModels::CInferTree
- <b>LBP:</b> Approximate inference based on the Loopy Belief Propagation (\a sum-product message-passing) algorithm @ref DirectGraphicalModels::CInferLBP 
- <b>Viterbi:</b> Approximate inference based on Viterbi (\a max-sum message-passing) algorithm @ref DirectGraphicalModels::CInferViterbi 

The corresponding classes are @b CInfer* (where @b * is the name of the method above). 

All of the inference classes may be also used for approximate decoding via function @ref DirectGraphicalModels::CInfer::decode()

@subsubsection sec_main_decode_decoding Decoding
- <b>Exact:</b> Exact decoding for small graphs with an exhaustive search @ref DirectGraphicalModels::CDecodeExact
- <b>TRW:</b> Approximate decoding using max-product loopy belief propagation (<a href="http://pub.ist.ac.at/~vnk/papers/TRW-S-PAMI.pdf" target="_blank">Convergent Tree-Reweighted Message Passing Algorithm</a>)
@ref DirectGraphicalModels::CDecodeTRW 

The corresponding classes are @b CDecode* (where @b * is the name of the method above). 

@subsection sec_main_paramest Parameter Estimation
DGM implements the following parameter estimation method:
- <b>Powell:</b> Powell search method @ref DirectGraphicalModels::CPowell

@subsection sec_main_fex Feature Extraction
Please refer to the @ref moduleFEX documentation


@subsection sec_main_sampling Sampling
DGM implements the following sampling method: 
- <b>Gauss:</b> Sampling from the multivariate gaussian distribution @ref DirectGraphicalModels::CNDGauss::getSample()

@section sec_main_links Quick Links
- @ref s3
- @ref demo
- <a href="http://project-10.de/forum/viewforum.php?f=31"><b>User Q&A forum</b></a>
- <a href="http://www.project-10.de/bugtracker/thebuggenie/dgmlib"><b>Report a bug</b></a>


@author Sergey G. Kosov, sergey.kosov@project-10.de
*/

/**
@defgroup moduleDGM DGM Module
@section sec_dgm_main Main DGM Module

	@defgroup moduleTrain Training
	@ingroup moduleDGM
	
		@defgroup moduleTrainNode Unary Potentials Training
		@ingroup moduleTrain

		@defgroup moduleTrainEdge Pairwise Potentials Training
		@ingroup moduleTrain

	@defgroup moduleGraph Graph Building
	@ingroup moduleDGM

	@defgroup moduleDecode Inference / Decoding
	@ingroup moduleDGM

	@defgroup moduleParamEst Parameter Estimation
	@ingroup moduleDGM

	@defgroup moduleVis Evaluation / Visualization
	@ingroup moduleDGM
*/

/**
@page s3 Installation
@section sec_install_cv Installing OpenCV
This library is based on OpenCV library v.3.1.0. In order to use the DGM library, the OpenCV library should be also installed.
-# Download the OpenCV library from <a href="http://sourceforge.net/projects/opencvlibrary/files/opencv-win/3.1.0/" target="_blank">sourcefourge</a>
-# Install the OpenCV library. You may follow the <a href="http://www.project-10.de/forum/viewtopic.php?f=23&t=198#p237" target="_blank">installation guide</a>

@section sec_install_dgm Installing DGM
-# Download the DGM library from <a href="http://research.project-10.de/dgm/">Project X Research</a>
-# Unzip it to your local folder (for example to disk @b C:\\, so the library path will be @b C:\\DGM\\)
-# In case you want to rebuild the library from the "Win32" / "x64" packages or you use the "Source" package follow these instructions, otherwise - skip this step
	-# Configure the paths in the DGM Visual Studio solution to match your installed OpenCV paths
	-# Perform Build -> Batch Build
	-# If you want to run the demo applications, you may need to copy OpenCV dll files to the @b C:\\DGM\\bin\\Release and/or @b C:\\DGM\\bin\\Debug folders
-# Specify the following paths and library
	-# Add to Configuration Properties -> C/C++ -> General -> Additional Include Directories the path @b C:\\DGM\\include\\
	-# Add to Configuration Properties -> Linker -> General -> Additional Library Directories the path @b C:\\DGM\\lib\\Release\\ and @b C:\\DGM\\lib\\Debug\\ for Release and Debug configurations accordingly
	-# Add to Configuration Properties -> Linker -> Input -> Additional Dependencies the libraries @b dgm142.lib, @b fex142.lib and @b dgm142d.lib, @b fex142d.lib for Release and Debug configurations accordingly
-# Copy the DGM dll files @b dgm142.dll, @b fex142.dll from @b C:\\DGM\\bin\\Release and @b dgm142d.dll, @b fex142d.dll from @b C:\\DGM\\bin\\Debug to your project's Relese and Debug folders.
*/

/**
@page demo Tutorials
<h2>How to use the code</h2>
The documentation for DGM consists of a series of demos, showing how to use DGM to perform various tasks. These demos also contain some tutorial material on graphical models.

- @subpage demo1d : An introduction to graphical models and to the tasks of inference and decoding on a set of simple examples:
  - @ref demo1d_exact : An introduction to graphical models and the tasks of decoding and inference on a small graphical model where we can do everything by hand. 
  - @ref demo1d_chain : An introduction to Markov independence properties on an example of a chain-structured graphical model, and to efficient dynamic programming 
						algorithms for inference. 
  - @ref demo1d_tree : This demo shows how to construct a tree-structured graphical model, for which also an exact message-passing inference algorithm exists. 
- @subpage demo2d : An example of more complicated graphical models, containing loops and built upon a binary 2-dimentional image. This example also shows the application of DGM to
					unsupervised segmentation.
- @subpage demofex : An introduction to the feature extraction, needed mainly for supervised learning.
- @subpage demotrain : An introdiction to the random model learning (training) in case when the training data is available.
- @subpage demovis : An example of usage the visualization module of the library for analysis and represention of the intermediate and final results of classification.

*/

/**
@page demo2d Demo 2D
In this demo, we consider the case of binary variables with attractive potentials. The original binary image \b Smile.png is degraded with noise, 
as showed at image \b Smile_noise.png. Using the DGM we restore the original image from its noised version and evaluate the results by
comparing the restored image with the original one.

<table align="center">
<tr>
	<td colspan="2"><center><b>Input</b></center></td>
	<td></td>
	<td><center><b>Output</b></center></td>
</tr>
<tr>
	<td><img src="smile.png"></td>
	<td><img src="smile_noise.png"></td>
	<td><img src="arrow.png"></td>
	<td><img src="smile_denoised.png"></td>
</tr>
<tr>
	<td><center><b>Smile.png</b></center></td>
	<td><center><b>Smile_noise.png</b></center></td>
	<td></td>
	<td><center><b>Restored Image</b></center></td>
</tr>
</table>

This example copies the idea from the <a href="http://www.di.ens.fr/~mschmidt/Software/UGM/graphCuts.html">GraphCuts UGM Demo</a>
@code
#include "DGM.h"
using namespace DirectGraphicalModels;

int main(int argv, char *argc[]) 
{
	const unsigned int	nStates	= 2;						// {true; false}
	
	// Reading parameters and images
	Mat		  img		= imread("Smile.png", 0);			// original image
	Mat		  noise		= imread("Smile_noise.png", 0);		// noised image
	int		  width		= img.cols;
	int		  height	= img.rows;
	
	CGraph	* graph		= new CGraph(nStates);
	CInfer  * decoder	= new CInferViterbi(graph);

	Mat nodePot(nStates, 1, CV_32FC1);						// node Potential (column-vector)
	Mat edgePot(nStates, nStates, CV_32FC1);				// edge Potential	
	
	// No training
	// Defynig the edge potential
	edgePot = CTrainEdgePotts::getEdgePotentials(10000, 2);
	// equivalent to:
	// ePot.at<float>(0, 0) = 1000;	ePot.at<float>(0, 1) = 1;
	// ePot.at<float>(1, 0) = 1;	ePot.at<float>(1, 1) = 1000;

	// ==================== Building and filling the graph ====================
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++) {
			float p = 1.0f - static_cast<float>(noise.at<byte>(y,x)) / 255.0f;
			nodePot.at<float>(0, 0) = p;
			nodePot.at<float>(1, 0) = 1.0f - p;
			size_t idx = graph->addNode(nodePot);
			if (y > 0) graph->addArk(idx, idx - 1, edgePot);
			if (x > 0) graph->addArk(idx, idx - width, edgePot);
			if ((y > 0) && (x > 0)) graph->addArk(idx, idx - width - 1, edgePot);
		} // y

	// =============================== Decoding ===============================
	printf("Decoding... ");
	int64 ticks = getTickCount();
	byte *optimalDecoding = decoder->decode(100);
	ticks =  getTickCount() - ticks;
	printf("Done! (%fms)\n", ticks * 1000 / getTickFrequency());

	
	// ====================== Evaluation / Visualization ======================
	for (int x = 0, i = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			noise.at<byte>(y,x) = 255 * optimalDecoding[i++];
	medianBlur(noise, noise, 3);

	float error = 0;
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (noise.at<byte>(y,x) != img.at<byte>(y,x)) error++;

	printf("Accuracy  = %.2f%%\n", 100 - 100 * error / (width * height));
	
	imshow("Image", noise);	

	cvWaitKey();

	return 0;
}
@endcode
*/

/**
@page demotrain Demo Train
In this demo, we consider the case when the training data is aviable. In this example the trainig data is represented in form of 
manually labelled image. The original image \b Original \b Image.jpg is a color-infrared image, and the grounftruth image \b GroundTruth \b Image.jpg
has 6 different classes, namely \a road, \a traffic \a island, \a grass, \a agriculture, \a tree and \a car (instances of which are not represented in image). 

In this example DGM uses 3 features extacted from the \b Original \b Image.jpg for training (Please refer to the @ref demofex for details). The same image then is used for the labelling. Finally, 
we evaluate the results by comparing the lebelled image with the groundtruth.


<table align="center">
<tr>
	<td colspan="3"><center><b>Input</b></center></td>
	<td></td>
	<td><center><b>Output</b></center></td>
</tr>
<tr>
  <td><img src="001_img_small.jpg"></td>
  <td><img src="001_fv_small.jpg"></td>
  <td><img src="001_gt_small.jpg"></td>
  <td><img src="arrow.png"></td>
  <td><img src="001_res_small.jpg"></td>
</tr>
<tr>
  <td><center><b>Original Image.jpg</b></center></td>
  <td><center><b>Feature Vector.jpg</b></center></td>
  <td><center><b>GroundTruth Image.jpg</b></center></td>
  <td></td>
  <td><center><b>Resulting Class Map</b></center></td>
</tr>
</table>

@code
#include "DGM.h"
using namespace DirectGraphicalModels;

int main(int argv, char *argc[])
{
	const CvSize		imgSize		= cvSize(400, 400);
	const int			width		= imgSize.width;
	const int			height		= imgSize.height;
	const unsigned int	nStates		= 6;	// {road, traffic island, grass, agriculture, tree, car} 		
	const unsigned int	nFeatures	= 3;		

	if (argv != 7) {
		print_help();
		return 0;
	}

	// Reading parameters and images
	int nodeModel	= atoi(argc[1]);															// node training model
	int edgeModel	= atoi(argc[2]);															// edge training model
	Mat img			= imread(argc[3], 1); resize(img, img, imgSize, 0, 0, INTER_LANCZOS4);		// image
	Mat fv			= imread(argc[4], 1); resize(fv,  fv,  imgSize, 0, 0, INTER_LANCZOS4);		// feature vector
	Mat gt			= imread(argc[5], 0); resize(gt,  gt,  imgSize, 0, 0, INTER_NEAREST);		// groundtruth

	CTrainNode		* nodeTrainer	= NULL; 
	CTrainEdge		* edgeTrainer	= NULL;
	CGraph			* graph			= new CGraph(nStates); 
	CInfer			* decoder		= new CInferLBP(graph);
	CMarker			* marker		= new CMarker(DEF_PALETTE_6);
	CCMat			* confMat		= new CCMat(nStates);
	float			  params[]		= {100, 0.01f};						
	size_t			  params_len;

	switch(nodeModel) {
		case 0: nodeTrainer = new CTrainNodeNaiveBayes(nStates, nFeatures);	break;
		case 1: nodeTrainer = new CTrainNodeGM(nStates, nFeatures);			break;
		case 2: nodeTrainer = new CTrainNodeGMM(nStates, nFeatures);		break;		
		case 3: nodeTrainer = new CTrainNodeCvGM(nStates, nFeatures);		break;
		case 4: nodeTrainer = new CTrainNodeCvGMM(nStates, nFeatures);		break;		
		case 5: nodeTrainer = new CTrainNodeCvRF(nStates, nFeatures);		break;		
		case 6: nodeTrainer = new CTrainNodeMsRF(nStates, nFeatures);		break;		
	}
	switch(edgeModel) {
		case 0: params[0] = 1;	// Emulate "No edges"
		case 1:	edgeTrainer = new CTrainEdgePotts(nStates, nFeatures);		params_len = 1; break;
		case 2:	edgeTrainer = new CTrainEdgePottsCS(nStates, nFeatures);	params_len = 2; break;
		case 3:	edgeTrainer = new CTrainEdgePrior(nStates, nFeatures);		params_len = 2; break;
		case 4:	
			CFeaturesConcatenator *pConcatenator = new CDiffFeaturesConcatenator(nFeatures);
			edgeTrainer = new CTrainEdgeConcat(nStates, nFeatures, pConcatenator);		
			params_len = 1;
			break;
	}

	// ==================== STAGE 1: Building the graph ====================
	printf("Building the Graph... ");
	int64 ticks = getTickCount();	
	for (int y = 0; y < height; y++) 
		for (int x = 0; x < width; x++) {
			size_t idx = graph->addNode();
			if (x > 0) 	 graph->addArk(idx, idx - 1);
			if (y > 0) 	 graph->addArk(idx, idx - width); 
		} // x
	ticks = getTickCount() - ticks;
	printf("Done! (%fms)\n", ticks * 1000 / getTickFrequency());

	// ========================= STAGE 2: Training =========================
	printf("Training... ");
	ticks = getTickCount();	
	
	// Node Training (copact notation)
	nodeTrainer->addFeatureVec(fv, gt);					
	nodeTrainer->train();	

	// Edge Training (comprehensive notation)
	Mat featureVector1(nFeatures, 1, CV_8UC1); 
	Mat featureVector2(nFeatures, 1, CV_8UC1); 	
	for (int y = 1; y < height; y++) {
		byte *pFv1 = fv.ptr<byte>(y);
		byte *pFv2 = fv.ptr<byte>(y - 1);
		byte *pGt1 = gt.ptr<byte>(y);
		byte *pGt2 = gt.ptr<byte>(y - 1);
		for (int x = 1; x < width; x++) {
			for (byte f = 0; f < nFeatures; f++) featureVector1.at<byte>(f, 0) = pFv1[nFeatures * x + f];		// featureVector1 = fv[x][y]

			for (byte f = 0; f < nFeatures; f++) featureVector2.at<byte>(f, 0) = pFv1[nFeatures * (x - 1) + f];	// featureVector2 = fv[x-1][y]
			edgeTrainer->addFeatureVecs(featureVector1, pGt1[x], featureVector2, pGt1[x-1]);
			edgeTrainer->addFeatureVecs(featureVector2, pGt1[x-1], featureVector1, pGt1[x]);

			for (byte f = 0; f < nFeatures; f++) featureVector2.at<byte>(f, 0) = pFv2[nFeatures * x + f];		// featureVector2 = fv[x][y-1]
			edgeTrainer->addFeatureVecs(featureVector1, pGt1[x], featureVector2, pGt2[x]);
			edgeTrainer->addFeatureVecs(featureVector2, pGt2[x], featureVector1, pGt1[x]);
		} // x
	} // y
	edgeTrainer->train();

	ticks = getTickCount() - ticks;
	printf("Done! (%fms)\n", ticks * 1000 / getTickFrequency());

	// ==================== STAGE 3: Filling the Graph =====================
	printf("Filling the Graph... ");
	ticks = getTickCount();
	Mat nodePot, edgePot;
	for (int y = 0, idx = 0; y < height; y++) {
		byte *pFv1 = fv.ptr<byte>(y);
		byte *pFv2 = (y > 0) ? fv.ptr<byte>(y - 1) : NULL;
		for (int x = 0; x < width; x++, idx++) {
			for (byte f = 0; f < nFeatures; f++) featureVector1.at<byte>(f, 0) = pFv1[nFeatures * x + f];			// featureVector1 = fv[x][y]
			nodePot = nodeTrainer->getNodePotentials(featureVector1);												// node potential
			graph->setNode(idx, nodePot);

			if (x > 0) {
				for (byte f = 0; f < nFeatures; f++) featureVector2.at<byte>(f, 0) = pFv1[nFeatures * (x - 1) + f];	// featureVector2 = fv[x-1][y]
				edgePot = edgeTrainer->getEdgePotentials(featureVector1, featureVector2, params, params_len);		// edge potential
				graph->setArk(idx, idx - 1, edgePot);
			} // if x
			if (y > 0) {
				for (byte f = 0; f < nFeatures; f++) featureVector2.at<byte>(f, 0) = pFv2[nFeatures * x + f];		// featureVector2 = fv[x][y-1]
				edgePot = edgeTrainer->getEdgePotentials(featureVector1, featureVector2, params, params_len);		// edge potential
				graph->setArk(idx, idx - width, edgePot);
			} // if y
		} // x
	} // y
	ticks = getTickCount() - ticks;
	printf("Done! (%fms)\n", ticks * 1000 / getTickFrequency());

	// ========================= STAGE 4: Decoding =========================
	printf("Decoding... ");
	ticks = getTickCount();
	byte *optimalDecoding = decoder->decode(10);
	ticks =  getTickCount() - ticks;
	printf("Done! (%fms)\n", ticks * 1000 / getTickFrequency());

	// ====================== Evaluation =======================	
	Mat solution(imgSize, CV_8UC1, optimalDecoding);
	confMat->estimate(gt, solution);																				// compare solution with the groundtruth
	char str[255];
	sprintf(str, "Accuracy = %.2f%%", confMat->getAccuracy());
	printf("%s\n", str);

	// ====================== Visualization =======================
	marker->markClasses(img, solution);
	rectangle(img, Point(width - 160, height- 18), Point(width, height), CV_RGB(0,0,0), -1);
	putText(img, str, Point(width - 155, height - 5), FONT_HERSHEY_SIMPLEX, 0.45, CV_RGB(225, 240, 255), 1, CV_AA);
	imwrite(argc[6], img);

	return 0;
}
@endcode
*/

/**
@page demovis Demo Visualization
DGM library has a rich set of tools for visualizing the data, intermediate and final results, as well as for interaction with created figures. It also provides  tools for analyzing the classification accuracy. 
In this example we took the @ref demotrain tutorial, simplified the training sections and expanded the visulaization part. First we estimate the quality of classification with 
<a href="https://en.wikipedia.org/wiki/Confusion_matrix">confusion matrix</a>, then we visualize the feature distributions for defined classes in the training dataset as well as the node and edge potentials. 
For user interaction capacity we define additional functions for handling the mouse clicks over the figures.

<table align="center">
<tr>
  <td><center><b>Confusion matrix</b></center></td>
  <td><center><b>Edge potential matrix</b></center></td>
  <td><center><b>Node potential vector</b></center></td>
  <td><center><b>Feature distribution histograms</b></center></td>
</tr>
<tr>
  <td valign="top"><img src="confusion_matrix.jpg"></td>
  <td valign="top"><img src="edge_potential.jpg"></td>
  <td valign="top"><img src="node_potential.jpg"></td>
  <td valign="top"><img src="histogram.jpg"></td>
</tr>
</table>

@code
#include "DGM.h"
using namespace DirectGraphicalModels;

// Global definitions
Mat histogramImg;

typedef struct {
	CGraph				* pGraph;
	CMarkerHistogram	* pMarker;
	int					  imgWidth;
} USER_DATA;

int main(int argv, char *argc[])
{
	const CvSize		imgSize		= cvSize(400, 400);
	const int			width		= imgSize.width;
	const int			height		= imgSize.height;
	const unsigned int	nStates		= 6;		// {road, traffic island, grass, agriculture, tree, car} 		
	const unsigned int	nFeatures	= 3;		

	if (argv != 4) {
		print_help();
		return 0;
	}

	// Reading parameters and images
	Mat img			= imread(argc[1], 1); resize(img, img, imgSize, 0, 0, INTER_LANCZOS4);		// image
	Mat fv			= imread(argc[2], 1); resize(fv,  fv,  imgSize, 0, 0, INTER_LANCZOS4);		// feature vector
	Mat gt			= imread(argc[3], 0); resize(gt,  gt,  imgSize, 0, 0, INTER_NEAREST);		// groundtruth

	CTrainNode			* nodeTrainer	 = new CTrainNodeNaiveBayes(nStates, nFeatures); 
	CTrainEdge			* edgeTrainer	 = new CTrainEdgePottsCS(nStates, nFeatures);
	float				  params[]		 = {400, 0.001f};						
	size_t				  params_len	 = 2;
	CGraph				* graph			 = new CGraph(nStates); 
	CInfer				* decoder		 = new CInferLBP(graph);
	// Define custom colors in RGB format for our classes (for visualization)
	vec_nColor_t		  palette;
	palette.push_back(std::make_pair(CV_RGB(64,  64,   64), "road"));
	palette.push_back(std::make_pair(CV_RGB(0,  255,  255), "tr. island"));
	palette.push_back(std::make_pair(CV_RGB(0,   255,   0), "grass"));
	palette.push_back(std::make_pair(CV_RGB(200, 135,  70), "agricult."));
	palette.push_back(std::make_pair(CV_RGB(64,  128,   0), "tree"));
	palette.push_back(std::make_pair(CV_RGB(255,   0,   0), "car"));
	// Define feature names for visualization
	char				* featureNames[] = {"NDVI", "Var. Int.", "Saturation"};	
	CMarkerHistogram	* marker		 = new CMarkerHistogram(nodeTrainer, palette, featureNames);
	CCMat				* confMat		 = new CCMat(nStates);

	// ==================== STAGE 1: Building the graph ====================
	printf("Building the Graph... ");
	int64 ticks = getTickCount();	
	for (int y = 0; y < height; y++) 
		for (int x = 0; x < width; x++) {
			size_t idx = graph->addNode();
			if (x > 0) 	 graph->addArk(idx, idx - 1);
			if (y > 0) 	 graph->addArk(idx, idx - width); 
		} // x
	ticks = getTickCount() - ticks;
	printf("Done! (%fms)\n", ticks * 1000 / getTickFrequency());

	// ========================= STAGE 2: Training =========================
	printf("Training... ");
	ticks = getTickCount();	
	nodeTrainer->addFeatureVec(fv, gt);										// Only Node Training 		
	nodeTrainer->train();													// Contrast-Sensitive Edge Model requires no training
	ticks = getTickCount() - ticks;
	printf("Done! (%fms)\n", ticks * 1000 / getTickFrequency());

	// ==================== STAGE 3: Filling the Graph =====================
	printf("Filling the Graph... ");
	ticks = getTickCount();
	Mat featureVector1(nFeatures, 1, CV_8UC1); 
	Mat featureVector2(nFeatures, 1, CV_8UC1); 
	Mat nodePot, edgePot;
	for (int y = 0, idx = 0; y < height; y++) {
		byte *pFv1 = fv.ptr<byte>(y);
		byte *pFv2 = (y > 0) ? fv.ptr<byte>(y - 1) : NULL;	
		for (int x = 0; x < width; x++, idx++) {
			for (byte f = 0; f < nFeatures; f++) featureVector1.at<byte>(f, 0) = pFv1[nFeatures * x + f];			// featureVector1 = fv[x][y]
			nodePot = nodeTrainer->getNodePotentials(featureVector1);												// node potential
			graph->setNode(idx, nodePot);

			if (x > 0) {
				for (byte f = 0; f < nFeatures; f++) featureVector2.at<byte>(f, 0) = pFv1[nFeatures * (x - 1) + f];	// featureVector2 = fv[x-1][y]
				edgePot = edgeTrainer->getEdgePotentials(featureVector1, featureVector2, params, params_len);		// edge potential
				graph->setArk(idx, idx - 1, edgePot);
			} // if x
			if (y > 0) {
				for (byte f = 0; f < nFeatures; f++) featureVector2.at<byte>(f, 0) = pFv2[nFeatures * x + f];		// featureVector2 = fv[x][y-1]
				edgePot = edgeTrainer->getEdgePotentials(featureVector1, featureVector2, params, params_len);		// edge potential
				graph->setArk(idx, idx - width, edgePot);
			} // if y
		} // x
	} // y
	ticks = getTickCount() - ticks;
	printf("Done! (%fms)\n", ticks * 1000 / getTickFrequency());

	// ========================= STAGE 4: Decoding =========================
	printf("Decoding... ");
	ticks = getTickCount();
	byte *optimalDecoding = decoder->decode(10);
	ticks =  getTickCount() - ticks;
	printf("Done! (%fms)\n", ticks * 1000 / getTickFrequency());

	// ====================== Evaluation =======================	
	Mat solution(imgSize, CV_8UC1, optimalDecoding);
	confMat->estimate(gt, solution);																				// compare solution with the groundtruth
	char str[255];
	sprintf(str, "Accuracy = %.2f%%", confMat->getAccuracy());
	printf("%s\n", str);

	// ====================== Visualization =======================
	marker->markClasses(img, solution);
	rectangle(img, Point(width - 160, height- 18), Point(width, height), CV_RGB(0,0,0), -1);
	putText(img, str, Point(width - 155, height - 5), FONT_HERSHEY_SIMPLEX, 0.45, CV_RGB(225, 240, 255), 1, CV_AA);
	imshow("Solution", img);
	
	// Feature distribution histograms
	histogramImg = marker->drawHistogram();
	imshow("Histogram", histogramImg);

	// Confusion matrix
	Mat cMat	= confMat->getConfusionMatrix();
	Mat cMatImg	= marker->drawConfusionMatrix(cMat, MARK_BW);
	imshow("Confusion Matrix", cMatImg);

	// Setting up handlers
	USER_DATA userData;
	userData.pGraph		= graph;
	userData.pMarker	= marker;
	userData.imgWidth	= width;
	cvSetMouseCallback("Solution",  solutiontWindowMouseHandler, &userData);
	cvSetMouseCallback("Histogram", histogramWindowMouseHandler, &userData);

	cvWaitKey();

	return 0;
}
@endcode

<b>Mouse Handler for drawing the node and edge potentials</b><br>
This mouse handler provides us with the capacity of user interaction with the \b Solution window. By clicking on the pixel of the solution image, we can derive the node potential vector from the graph node,
associated with the chosen pixel, and visualize it. In this example, each graph node has four edges, which connect the node with its direct four neighbors; we visualize one edge potential matrix,
corresponding to one of these four edge potentials. The visualization of the node and edge potentials helps to analyze the local potential patterns.

@code
void solutiontWindowMouseHandler(int Event, int x, int y, int flags, void *param)
{
	USER_DATA	* pUserData	= static_cast<USER_DATA *>(param);
	if (Event == CV_EVENT_LBUTTONDOWN) {
		Mat			  pot, potImg;
		size_t		  node_id	= pUserData->imgWidth * y + x;

		// Node potential
		pUserData->pGraph->getNode(node_id, pot);
		potImg = pUserData->pMarker->drawPotentials(pot, MARK_BW);
		imshow("Node Potential", potImg);

		// Edge potential
		vec_size_t child_nodes;
		pUserData->pGraph->getChildNodes(node_id, child_nodes);
		if (child_nodes.size() > 0) {
			pUserData->pGraph->getEdge(node_id, child_nodes.at(0), pot);
			potImg = pUserData->pMarker->drawPotentials(pot, MARK_BW);
			imshow("Edge Potential", potImg);
		}

		pot.release();
		potImg.release();
	}
}
@endcode

<b>Mouse Handler for drawing the feature distribution histograms</b><br>
This mouse handler allows for user interaction with \b Histogram window. Its capable to visualize the feature distributions separately for each class. User can chose the needed class by clicking on the 
color box near to the class name. These feature distributions allow for analyzing the separability of the classes in the feature sapce.

@code
void histogramWindowMouseHandler(int Event, int x, int y, int flags, void *param)
{
	USER_DATA	* pUserData	= static_cast<USER_DATA *>(param);
	if (Event == CV_EVENT_LBUTTONDOWN) {
		CvScalar color;
		color.val[0] = histogramImg.at<byte>(y, 3 * x + 0);	// Blue
		color.val[1] = histogramImg.at<byte>(y, 3 * x + 1);	// Green
		color.val[2] = histogramImg.at<byte>(y, 3 * x + 2);	// Red

		histogramImg.release();
		histogramImg = pUserData->pMarker->drawHistogram(color);
		imshow("Histogram", histogramImg);
	}
}
@endcode


*/