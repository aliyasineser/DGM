// Extended (pairwise) Layered Graph class interface;
// Written by Sergey Kosov in 2016 for Project X
#pragma once

#include "types.h"

namespace DirectGraphicalModels
{
	class CGraphPairwise;
	class CTrainEdge;
	class CTrainLink;


	/**
	* @brief Graph types
	* @details Define the grid of edges, connecting nodes of the graph
	*/
	enum graphType {
		GRAPH_EDGES_NONE = 0,		///< No edges
		GRAPH_EDGES_GRID = 1,		///< Vertical and horizontal edges
		GRAPH_EDGES_DIAG = 2,		///< Diagonal edges
		GRAPH_EDGES_LINK = 4		///< Links (inter-layer edges)
	};

	// ================================ Extended Graph Class ================================
	/**
	* @brief Extended Pairwise Layered graph class
	* @ingroup moduleGraph
	* @details This graph class provides additional functionality, when the multi-layer graph is used for 2d image classification
	* @author Sergey G. Kosov, sergey.kosov@project-10.de
	*/
	class CGraphLayered
	{
	public:
		/**
		* @brief Constructor
		* @param graph The graph
		* @param nLayers The number of layers
		* @param gType The graph type. (Ref. @ref graphType)
		*/
		DllExport CGraphLayered(CGraphPairwise &graph, word nLayers, byte gType = GRAPH_EDGES_GRID) : m_graph(graph), m_nLayers(nLayers), m_gType(gType), m_size(cv::Size(0, 0)) {}
		DllExport ~CGraphLayered(void) {}

		/**
		* @brief Builds a graph, which fits the image resolution
		* @details The graph is built under the assumption that each graph node is connected with arcs to its direct four neighbours.
		* @param graphSize The size of the graph
		*/
		DllExport void addNodes(cv::Size graphSize);
		/**
		* @brief Fills the graph nodes with potentials
		* @details
		* > This function supports PPL
		* @param potBase A block of potentials for the base layer: Mat(type: CV_32FC(nStatesBase))
		* @param potOccl A block of potentials for the occlusion layer: Mat(type: CV_32FC(nStatesOccl))
		*/
		DllExport void setNodes(const Mat &potBase, const Mat &potOccl);
		/**
		* @brief Fills the graph edges with potentials
		* @details This function uses \b edgeTrainer class in oerder to achieve edge potentials from feature vectors, stored in \b featureVectors
		* and fills with them the graph edges
		* > This function supports PPL
		* @param edgeTrainer A pointer to the edge trainer
		* @param linkTrainer A pointer to tht link (inter-layer edge) trainer
		* @param featureVectors Multi-channel matrix, each element of which is a multi-dimensinal point: Mat(type: CV_8UC<nFeatures>)
		* @param vParams Array of control parameters. Please refer to the concrete model implementation of the CTrainEdge::calculateEdgePotentials() function for more details
		* @param edgeWeight The weighting parameter for (within-layer) edges 
		* @param linkWeight The weighting parameter for (inter-layer) edges, \a i.e. links
		*/
		DllExport void fillEdges(const CTrainEdge *edgeTrainer, const CTrainLink *linkTrainer, const Mat &featureVectors, const vec_float_t &vParams, float edgeWeight = 1.0f, float linkWeight = 1.0f);
		/**
		* @brief Fills the graph edges with potentials
		* @details This function uses \b edgeTrainer class in oerder to achieve edge potentials from feature vectors, stored in \b featureVectors
		* and fills with them the graph edges
		* > This function supports PPL
		* @param edgeTrainer A pointer to the edge trainer
		* @param linkTrainer A pointer to tht link (inter-layer edge) trainer
		* @param featureVectors Vector of size \a nFeatures, each element of which is a single feature - image: Mat(type: CV_8UC1)
		* @param vParams Array of control parameters. Please refer to the concrete model implementation of the CTrainEdge::calculateEdgePotentials() function for more details
		* @param edgeWeight The weighting parameter for (within-layer) edges
		* @param linkWeight The weighting parameter for (inter-layer) edges, \a i.e. links
		*/
		DllExport void fillEdges(const CTrainEdge *edgeTrainer, const CTrainLink *linkTrainer, const vec_mat_t &featureVectors, const vec_float_t &vParams, float edgeWeight = 1.0f, float linkWeight = 1.0f);
		/**
		* @brief Assign the edges, which cross the given line to the grop \b group.
		* @details The line is given by the equation: <b>A</b>x + <b>B</b>y + <b>C</b> = 0. \b A and \b B are not both equal to zero.
		* @param A Constant line parameter
		* @param B Constant line parameter
		* @param C Constant line parameter
		* @param group New group ID
		*/
		DllExport void defineEdgeGroup(float A, float B, float C, byte group);
		/**
		* @brief Sets potential \b pot to all edges in the group \b group
		* @param group The edge group ID
		* @param pot %Edge potential matrix: Mat(size: nStates x nStates; type: CV_32FC1)
		*/
		DllExport void setGroupPot(byte group, const Mat &pot);
		/**
		* @brief Returns the type of the graph
		* @returns The type of the graph (Ref. @ref graphType)
		*/
		DllExport byte getType(void) const { return m_gType; }
		/**
		* @brief Returns the size of the graph
		* @return The size of the Graph
		*/
		DllExport cv::Size getSize(void) const { return m_size; }


	private:
		CGraphPairwise	& m_graph;			///< The graph
		word			  m_nLayers;		///< Number of layers
		byte			  m_gType;			///< Graph type (Ref. @ref graphType)
		cv::Size			  m_size;			///< Size of the graph
	};
}
