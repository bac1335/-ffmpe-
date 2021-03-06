INCLUDEPATH += $$PWD/include
DEFINES += __STDC_CONSTANT_MACROS __STDC_LIMIT_MACROS

LIBS += -L$$PWD/lib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample -lswscale
CONFIG += c++11

HEADERS += \
    $$PWD/ffmpeginclude.h \
    $$PWD/include/_mingw.h \
    $$PWD/include/inttypes.h \
    $$PWD/include/libavcodec/avcodec.h \
    $$PWD/include/libavcodec/avfft.h \
    $$PWD/include/libavcodec/dxva2.h \
    $$PWD/include/libavcodec/old_codec_ids.h \
    $$PWD/include/libavcodec/vaapi.h \
    $$PWD/include/libavcodec/vda.h \
    $$PWD/include/libavcodec/vdpau.h \
    $$PWD/include/libavcodec/version.h \
    $$PWD/include/libavcodec/xvmc.h \
    $$PWD/include/libavdevice/avdevice.h \
    $$PWD/include/libavdevice/version.h \
    $$PWD/include/libavfilter/asrc_abuffer.h \
    $$PWD/include/libavfilter/avcodec.h \
    $$PWD/include/libavfilter/avfilter.h \
    $$PWD/include/libavfilter/avfiltergraph.h \
    $$PWD/include/libavfilter/buffersink.h \
    $$PWD/include/libavfilter/buffersrc.h \
    $$PWD/include/libavfilter/version.h \
    $$PWD/include/libavformat/avformat.h \
    $$PWD/include/libavformat/avio.h \
    $$PWD/include/libavformat/version.h \
    $$PWD/include/libavutil/adler32.h \
    $$PWD/include/libavutil/aes.h \
    $$PWD/include/libavutil/attributes.h \
    $$PWD/include/libavutil/audio_fifo.h \
    $$PWD/include/libavutil/audioconvert.h \
    $$PWD/include/libavutil/avassert.h \
    $$PWD/include/libavutil/avconfig.h \
    $$PWD/include/libavutil/avstring.h \
    $$PWD/include/libavutil/avutil.h \
    $$PWD/include/libavutil/base64.h \
    $$PWD/include/libavutil/blowfish.h \
    $$PWD/include/libavutil/bprint.h \
    $$PWD/include/libavutil/bswap.h \
    $$PWD/include/libavutil/buffer.h \
    $$PWD/include/libavutil/channel_layout.h \
    $$PWD/include/libavutil/common.h \
    $$PWD/include/libavutil/cpu.h \
    $$PWD/include/libavutil/crc.h \
    $$PWD/include/libavutil/dict.h \
    $$PWD/include/libavutil/downmix_info.h \
    $$PWD/include/libavutil/error.h \
    $$PWD/include/libavutil/eval.h \
    $$PWD/include/libavutil/ffversion.h \
    $$PWD/include/libavutil/fifo.h \
    $$PWD/include/libavutil/file.h \
    $$PWD/include/libavutil/frame.h \
    $$PWD/include/libavutil/hmac.h \
    $$PWD/include/libavutil/imgutils.h \
    $$PWD/include/libavutil/intfloat.h \
    $$PWD/include/libavutil/intfloat_readwrite.h \
    $$PWD/include/libavutil/intreadwrite.h \
    $$PWD/include/libavutil/lfg.h \
    $$PWD/include/libavutil/log.h \
    $$PWD/include/libavutil/lzo.h \
    $$PWD/include/libavutil/macros.h \
    $$PWD/include/libavutil/mathematics.h \
    $$PWD/include/libavutil/md5.h \
    $$PWD/include/libavutil/mem.h \
    $$PWD/include/libavutil/murmur3.h \
    $$PWD/include/libavutil/old_pix_fmts.h \
    $$PWD/include/libavutil/opt.h \
    $$PWD/include/libavutil/parseutils.h \
    $$PWD/include/libavutil/pixdesc.h \
    $$PWD/include/libavutil/pixfmt.h \
    $$PWD/include/libavutil/random_seed.h \
    $$PWD/include/libavutil/rational.h \
    $$PWD/include/libavutil/replaygain.h \
    $$PWD/include/libavutil/ripemd.h \
    $$PWD/include/libavutil/samplefmt.h \
    $$PWD/include/libavutil/sha.h \
    $$PWD/include/libavutil/sha512.h \
    $$PWD/include/libavutil/stereo3d.h \
    $$PWD/include/libavutil/time.h \
    $$PWD/include/libavutil/timecode.h \
    $$PWD/include/libavutil/timestamp.h \
    $$PWD/include/libavutil/version.h \
    $$PWD/include/libavutil/xtea.h \
    $$PWD/include/libpostproc/postprocess.h \
    $$PWD/include/libpostproc/version.h \
    $$PWD/include/libswresample/swresample.h \
    $$PWD/include/libswresample/version.h \
    $$PWD/include/libswscale/swscale.h \
    $$PWD/include/libswscale/version.h \
    $$PWD/include/stdint.h

