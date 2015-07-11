#include "asset.h"
#include "directx.h"

namespace anim
{
	//�P�s�󂯎��,��؂�Ńp�[�X���ĕԂ�
	std::vector< std::string > graph_loader::parse( std::string const & str ) const
	{
		std::vector< std::string > result;

		boost::split( result, str, boost::is_any_of( "," ) );

		return result;
	}

	void load_graph( std::vector< std::string > const & strs, std::map< std::string, int > & asset_map )
	{
		enum graph_format
		{ 
			asset_name,
			graph_name,
			size
		};

		if( strs.size() != graph_format::size )
		{
			return;
		}

		//�摜��ǂݍ���œo�^
		//directX�ւ̓o�^(load_graph�œo�^�����)
		//�Ԃ��Ă���̂͌��݂̂Ƃ���ginfo��vector�̃C���f�b�N�X
		auto const graph_handle = graphic_api::load_graph( strs[ graph_format::graph_name ] );

		//load_graph�œǂݍ��񂾉摜�n���h����ǂݏo����悤��
		//asset�ɓo�^( assetname - handle )��map�������(�����\�[�X�̊J���͎����ł����)
		asset_map[ strs[ graph_format::asset_name ] ] = graph_handle;
	}

	//"�ǂݍ��މ摜�ꗗ"���L�ڂ��ꂽ�t�@�C����ǂݍ���ň�s����vector�Ɋi�[���ĕԂ�
	boost::optional< std::vector< std::string > > graph_loader::load_anim( std::string const & graphlist_filename )
	{
		std::ifstream graphlist( graphlist_filename );

		if( !graphlist )
		{
			return boost::none;
		}

		std::vector< std::string > contents;

		while( !graphlist.eof() )
		{
			std::string tmp;
			std::getline( graphlist, tmp );

			if( tmp[ 0 ] != '#' && tmp != "" )
				contents.push_back( tmp );
		}

		return boost::optional< std::vector< std::string > >( contents );
	}


}





