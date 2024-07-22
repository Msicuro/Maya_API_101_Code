#pragma once
/**
* @author Mattia Sicuro
* @date 7/18/2024
* @version latest version: 1.0
*
* node name: basicNode
* details: This node lets you convert a curve arc length into a U param
* example create node: (MEL) createNode basicNode
* 
*/

#ifndef basicNode_H
#define basicNode_H


#include <maya/MTypeId.h>
#include <maya/MPxNode.h>


class basicNode:public MPxNode
{
public:
	virtual MStatus compute(const MPlug& plug, MDataBlock& data);
	static void* creator();
	static MStatus initialize();

public:
	// The node ID
	static MTypeId typeId;
	// The input value
	static MObject inputVal;
	// This is the input curve
	static MObject inputCurve;
	// This is the output attribute holding the computed data
	static MObject outputVal;

};

#endif