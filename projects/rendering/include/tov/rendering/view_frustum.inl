namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	template<>
	inline typename ViewFrustumProjection<ProjectionType::PERSPECTIVE>::ProjectionParameters
	ViewFrustumProjection<ProjectionType::PERSPECTIVE>::calculateProjectionParameters() noexcept
	{
		ProjectionParameters parameters;

		math::Radian halfThetaY = this->mFieldOfViewY / 2;
		float tanThetaY = math::tan(halfThetaY);
		float tanThetaX = tanThetaY * this->mAspectRatio;

		float halfWidthNear = this->mNearDistance * tanThetaX;
		float halfHeightNear = this->mNearDistance * tanThetaY;

		parameters.left = -halfWidthNear;
		parameters.right = halfWidthNear;
		parameters.bottom = -halfHeightNear;
		parameters.top = halfHeightNear;

		return parameters;
	}

	template<>
	inline void ViewFrustumProjection<ProjectionType::PERSPECTIVE>::buildProjectionMatrix() noexcept
	{
		ProjectionParameters parameters = this->calculateProjectionParameters();

		float invertedWidth = 1.0f / (parameters.right - parameters.left);
		float invertedHeight = 1.0f / (parameters.top - parameters.bottom);
		float invertedDepth = 1.0f / (mFarDistance - mNearDistance);

		float A = 2.0f * mNearDistance * invertedWidth;
		float B = 2.0f * mNearDistance * invertedHeight;
		float C = (parameters.right + parameters.left) * invertedWidth;
		float D = (parameters.top + parameters.bottom) * invertedHeight;
		float q, qn;

		q = -(mFarDistance + mNearDistance) * invertedDepth;
		qn = -2.0f * (mFarDistance * mNearDistance) * invertedDepth;

		// Right hand projection matrix
		// [ A 0 C 0  ]
		// [ 0 B D 0  ]
		// [ 0 0 q qn ]
		// [ 0 0 -1 0 ]

		mProjectionMatrix = math::Matrix4::ZERO;
		mProjectionMatrix[0][0] = A;
		mProjectionMatrix[0][2] = C;
		mProjectionMatrix[1][1] = B;
		mProjectionMatrix[1][2] = D;
		mProjectionMatrix[2][2] = q;
		mProjectionMatrix[2][3] = qn;
		mProjectionMatrix[3][2] = -1;
	}

	TOV_NAMESPACE_END // rendering
}