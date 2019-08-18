/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

#include "iodefine.h"
#include <machine.h>


void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void InitClock( void )
{
	// �v���e�N�g�����i�N���b�N������H�֘A / ���샂�[�h�A����d�͒ጸ�@�\�A�\�t�g�E�F�A���Z�b�g�֘A / VRCR�j
	SYSTEM.PRCR.WORD = 0xA507;
	
	// �d�����M�����[�^���䃌�W�X�^(�V�X�e���N���b�N��ύX���邽�߁A"00h"���������ށj
	//SYSTEM.VRCR = 0x00;
	
	// ���C���N���b�N���U����J�n
	SYSTEM.MOSCWTCR.BYTE = 0x0D;		// ���C���N���b�N���U���莞�ԁF131072�T�C�N��
	SYSTEM.MOSCCR.BIT.MOSTP = 0;		// ���C���N���b�N���U����J�n
	while( SYSTEM.MOSCCR.BIT.MOSTP != 0 );	// �ݒ芮���҂�
	
	// PLL���U����J�n
	SYSTEM.PLLCR.WORD = 0x0901;		// 20HMz / 2 * 10 = 100MHz
	SYSTEM.PLLWTCR.BYTE = 0x0D;		// PLL���U���莞�ԁF1048576�T�C�N��
	SYSTEM.PLLCR2.BIT.PLLEN = 0;		// PLL���U����J�n
	while( SYSTEM.PLLCR2.BIT.PLLEN != 0 );  // �ݒ芮���҂�
	
	// �������샂�[�h�ɑJ��
	SYSTEM.OPCCR.BIT.OPCM = 0;		// �������샂�[�h
	while( SYSTEM.OPCCR.BIT.OPCMTSF != 0 );	// �J�ڊ����܂ő҂�
	
	// ���Ӄ��W���[���N���b�N(PCLKD)�F50MHz(100MHz / 2)
	// ���Ӄ��W���[���N���b�N(PCLKB)�F25MHz(100MHz / 4)
	// �O���o�X�N���b�N(BCLK)       �F25MHz(100Mhz / 4)
	// �V�X�e���N���b�N(ICLK)       �F50MHz(100MHz / 2)
	// FlashIF�N���b�N(FCLK)        �F25MHz(100MHz / 4)
	SYSTEM.SCKCR.LONG = 0x21021211;
	while( SYSTEM.SCKCR.LONG != 0x21021211 ); // �ݒ芮���҂�
		
	// PLL��H�I��
	SYSTEM.SCKCR3.WORD = 0x0400;		// PLL��H�I��
	while( SYSTEM.SCKCR3.WORD != 0x0400 );  // �ݒ芮���҂�
	
	// �����I���`�b�v�I�V���[�^��~
	SYSTEM.HOCOCR.BYTE = 0x01;		// HOCO��~
	while( SYSTEM.HOCOCR.BYTE != 0x01 );	// �ݒ芮���҂�
	
	// �ᑬ�I���`�b�v�I�V���[�^��~
	SYSTEM.LOCOCR.BYTE = 0x01;		// LOCO��~
	while( SYSTEM.LOCOCR.BYTE != 0x01 );	// �ݒ芮���҂�
	
	// �T�u�N���b�N���U���~
	SYSTEM.SOSCCR.BYTE = 0x01;		// �T�u�N���b�N���U���~
	while( SYSTEM.SOSCCR.BYTE != 0x01 );	// �ݒ芮���҂�
	RTC.RCR3.BYTE = 0x0C;			// RTC[�T�u�N���b�N���U���~, �W��CL�p�h���C�u�\��]
	while( RTC.RCR3.BYTE != 0x0C );		// �ݒ芮���҂�
	
	// �v���e�N�g�ݒ�
	SYSTEM.PRCR.WORD = 0xA500;	
}

void InitBCLK( void )
{
	// PORT53��BCLK�o�͂ɐ؂�ւ���
	PORT5.PMR.BIT.B3 = 1;
	
	// �v���e�N�g�����i�N���b�N������H�֘A / ���샂�[�h�A����d�͒ጸ�@�\�A�\�t�g�E�F�A���Z�b�g�֘A�j
	SYSTEM.PRCR.WORD = 0xA503;
	
	// BCLK�[�q�o�͒�~
	SYSTEM.SCKCR.BIT.PSTOP1 = 1;		// BCLK�[�q�o�͒�~
	while( SYSTEM.SCKCR.BIT.PSTOP1 != 1 );	// �ݒ芮���҂�
		
	// BCLK�[�q�o�͑I���F12.5MHz(25MHz / 2)
	SYSTEM.BCKCR.BYTE = 0x01;		// BCLK��2����
	while( SYSTEM.BCKCR.BYTE != 0x01 );	// �ݒ芮���҂�

	// �O���o�X��L���ɂ���
	SYSTEM.SYSCR0.WORD = 0x5A03;		// �O���o�X�L��
	while( SYSTEM.SYSCR0.BIT.EXBE != 1 );	// �ݒ芮���҂�

	// BCLK�[�q�o�͓���
	SYSTEM.SCKCR.BIT.PSTOP1 = 0;		// BCLK�[�q�o�͓���
	while( SYSTEM.SCKCR.BIT.PSTOP1 != 0 );	// �ݒ芮���҂�
	
	// �v���e�N�g�ݒ�
	SYSTEM.PRCR.WORD = 0xA500;	
}

void InitTimer( void )
{
	// �v���e�N�g�����i���샂�[�h�A����d�͒ጸ�@�\�A�\�t�g�E�F�A���Z�b�g�֘A�j
	SYSTEM.PRCR.WORD = 0xA502;
	
	// �R���y�A�}�b�`�^�C�}(���j�b�g0)���W���[���X�g�b�v�ݒ�r�b�g
	MSTP(CMT0) = 0;				// ��ԉ���
	
	// CMI0�����ݗv������
	IEN( CMT0, CMI0 ) = 1;
	
	// CMI0�����݂̊����ݗD�惌�x����1�ɐݒ�
	IPR( CMT0, CMI0 ) = 1;
	
	// �v���e�N�g�ݒ�
	SYSTEM.PRCR.WORD = 0xA500;	

	
	CMT0.CMCR.WORD = 0x00C0;	// �R���y�A�}�b�`�����݋���, �N���b�N�I���r�b�g(PCLKB(25MHz) / 8)
	CMT0.CMCOR = 3125;		// 1ms�̃J�E���g
	CMT0.CMCNT = 0;			// �R���y�A�}�b�`�^�C�}�J�E���^������
	CMT.CMSTR0.BIT.STR0 = 1;	// CMT0.CMCNT�J�E���^�̃J�E���g����J�n
}	
	

void main(void)
{
	// �N���b�N�ݒ�
	InitClock( );
	
	// BCLK�o�͐ݒ�
	InitBCLK( );
	
	// �^�C�}�[�ݒ�
	InitTimer( );
	
	// PORT B1���o�̓|�[�g�ɂ���
	PORTB.PDR.BIT.B0 = 1;
	
	while( 1 )
	{
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
