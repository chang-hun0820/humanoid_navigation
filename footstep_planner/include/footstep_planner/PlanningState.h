// SVN $HeadURL$
// SVN $Id$

/*
 * A footstep planner for humanoid robots
 *
 * Copyright 2010-2011 Johannes Garimort, Armin Hornung, University of Freiburg
 * http://www.ros.org/wiki/footstep_planner
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FOOTSTEP_PLANNER_PLANNINGSTATE_H_
#define FOOTSTEP_PLANNER_PLANNINGSTATE_H_

#include <footstep_planner/helper.h>


namespace footstep_planner
{
	/**
	 * @brief A class representing the robot's pose (i.e. position and
	 * orientation). More precisely the planning state points to the robot's
	 * supporting leg.
	 *
	 * Since the underlying SBPL is working on discretized states the planning
	 * states are also discretized positions and orientations. This is done by
	 * fitting the positions into a grid and the orientations into bins.
	 * (NOTE: the resolution of the planning cells is likely to differ from the
	 * resolution of the grid map.)
	 *
	 * The SBPL can access each planning state via an unique ID. Furthermore
	 * each planning state can be identified by an (ununique) hash tag generated
	 * from its position, location and supporting leg.
	 */
	class PlanningState
	{
	public:
		/**
		 * @brief x, y and theta represent the global (continuous) position and
		 * orientation of the robot's support leg.
		 *
		 * @param leg The supporting leg.
		 * @param cell_size The size of each grid cell discretizing the
		 * position.
		 * @param num_angle_bins The number of bins discretizing the
		 * orientation.
		 * @param max_hash_size
		 */
	    PlanningState(double x, double y, double theta, Leg leg,
                      double cell_size, int num_angle_bins, int max_hash_size);

	    /**
	     * @brief x, y and theta as discrete bin values (as used internally by
	     * the planner).
	     */
	    PlanningState(int x, int y, int theta, Leg leg,
                      double cell_size, int num_angle_bins, int max_hash_size);

	    /// Create a (discrete) PlanningState from a (continuous) State.
        PlanningState(const State& s, double cell_size, int num_angle_bins,
                      int max_hash_size);

        /// Copy constructor.
		PlanningState(const PlanningState& s);

		~PlanningState();

		bool operator ==(const PlanningState& s2) const;
		bool operator !=(const PlanningState& s2) const;

		/**
		 * @brief Used to attach such an unique ID to the planning state. (This
		 * cannot be done in the constructor since often such an ID is not known
		 * when the planning state is created.)
		 */
		void setId(unsigned int id) { ivId = id; };

		Leg getLeg() const { return ivLeg; };
		int getTheta() const { return ivTheta; };
		int getX() const { return ivX; };
		int getY() const { return ivY; };

		/**
		 * @return The (ununique) hash tag used to identify the planning
		 * state.
		 */
		unsigned int getHashTag() const { return ivHashTag; };

		/**
		 * @return The (unique) ID used within the SBPL to access the
		 * planning state.
		 */
		int getId() const { return ivId; };

		/// @brief Computes the continuous State the PlanningState represents.
		State getState(double cell_size, int num_angle_bins);

	private:
		/// Value of the grid cell the position's x value is fitted into.
		int ivX;
		/// Value of the grid cell the position's y value is fitted into.
		int ivY;
		/// Number of the bin the orientation is fitted into.
		int ivTheta;
		/// The supporting leg.
		Leg	ivLeg;

		/// The (unique) ID of the planning state.
	    int ivId;

	    /// The (ununique) hash tag of the planning state.
		unsigned int ivHashTag;
	};
}
#endif  // FOOTSTEP_PLANNER_PLANNINGSTATE_H_
