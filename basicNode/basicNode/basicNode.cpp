#include "basicNode.h"

#include <maya/MFnNumericAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MFloatPoint.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MPlug.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MDataHandle.h>

#include <cmath>

// Define type id declared in header file
MTypeId basicNode::typeId(0x80004);

// Define attributes declared in header file from the basicNode class
MObject basicNode::inputVal;
MObject basicNode::inputCurve;
MObject basicNode::outputVal;

// Define the basicNode Class methods
void* basicNode::creator()
{
	return new basicNode();
}

MStatus basicNode::initialize()
{
	// Declare all the needed attribute function sets/variables
	MFnNumericAttribute numFn;
	MFnTypedAttribute typedFn;

	MStatus status;

	// Create and add the attributes to the node
	inputVal = numFn.create("inputValue", "iv", MFnNumericData::kDouble, 0, &status);
	numFn.setKeyable(true);
	numFn.setWritable(true);
	numFn.setStorable(true);
	addAttribute(inputVal);

	inputCurve = typedFn.create("inputCurve", "incv", MFnData::kNurbsCurve);
	typedFn.setKeyable(true);
	typedFn.setWritable(true);
	typedFn.setStorable(true);
	addAttribute(inputCurve);

	outputVal = numFn.create("outputValue", "ov", MFnNumericData::kDouble);
	numFn.setKeyable(false);
	numFn.setWritable(false);
	numFn.setStorable(false);
	addAttribute(outputVal);

	// Specify which input attributes affect which output attributes
	attributeAffects(inputVal, outputVal);
	attributeAffects(inputCurve, outputVal);

	return MS::kSuccess;

}

MStatus basicNode::compute(const MPlug& plug, MDataBlock& data)
{
	// Check if the plugs attribute is the same as the output value using custom == operator
	if (plug == outputVal)
	{
		// Read the input
		double inVal = data.inputValue(inputVal).asDouble();
		MObject crvV = data.inputValue(inputCurve).asNurbsCurve();

		// Compute corresponding parameter
		MFnNurbsCurve crvFn(crvV);
		double outVal = crvFn.findParamFromLength(inVal);

		// Set the output
		data.outputValue(outputVal).set(outVal);
		data.outputValue(outputVal).setClean();
	}

	return MS::kSuccess;
}