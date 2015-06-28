#pragma once
#include <utility>
#include <cmath>

namespace game_main
{

	namespace player
	{
		struct position
		{
			double x_ = 0;
			double y_ = 0;

			position & operator+=( position const & p )
			{
				x_ += p.x_;
				y_ += p.y_;

				return *this;
			}

			position & operator-=( position const & p )
			{
				x_ -= p.x_;
				y_ -= p.y_;

				return *this;
			}

			position && operator+( position const & p ) const
			{
				position tmp;

				tmp += p;

				return std::move( tmp );
			}

			position && operator-( position const & p ) const
			{
				position tmp;

				tmp -= p;

				return std::move( tmp );
			}

			position()
			{
			}

			position( double const x, double const y ) : x_( x ), y_( y )
			{
			}
		};

		struct angle_velocity
		{
			position move()
			{
				return position( vel_x_, vel_y_ );
			}

			void angle( double const angle )
			{
				angle_ = angle;
				base_vx_ = std::cos( angle_ );
				base_vy_ = std::sin( angle_ );
				vel_in(); //speed * base_vx,vy
			}

			//velocityÇíºê⁄åàÇﬂÇÈ -> angleÇÃââéZ, base_vxÅCbase_vyÇÃê›íËÇ‡çsÇ§
			void set_velocity( double const vel_x, double const vel_y )
			{
				angle_in( std::atan2( vel_y, vel_x ) );

				if( base_vx_ != 0 )
				{
					speed_ = vel_x / base_vx_;
				}
				else
				{
					speed_ = vel_y / base_vy_;
				}
				vel_in(); //speed * base_vx,vy
			}

		private:
			double base_vx_ = 0.0;
			double base_vy_ = 0.0;

			double angle_ = 0.0;
			double speed_ = 0.0;

			//pre caluculated
			double vel_x_ = 0.0;
			double vel_y_ = 0.0;

			void vel_in()
			{
				vel_x_ = speed_ * base_vx_;
				vel_y_ = speed_ * base_vy_;
			}

			void angle_in( double const angle )
			{
				angle_ = angle;
				base_vx_ = std::cos( angle_ );
				base_vy_ = std::sin( angle_ );
			}

		};

		constexpr int DEFAULT_LIFE = 0;

		class system_param
		{
		public:

		private:
			int life_ = DEFAULT_LIFE;;

		};


		class player_class
		{
		public:
			enum STATE
			{
				E_STATE_INIT,
				E_STATE_NORMAL,
				E_STATE_DIE,
				E_STATE_BOMB,
				E_STATE_CLEAR
			};

			player_class();
			
			void move();
			
		private:
			angle_velocity velocity_;
			int state_;
			bool control_ = false;

		};
	}



}


