import { palette, paletteMantine } from '@/define';
import Channel from './Channel';

import { Box, alpha } from '@mantine/core';

type EnvelopeGraphProps = {
  width?: number;
  height?: number;
};

export default function EnvelopeGraph({
  width = 300,
  height = 300,
}: EnvelopeGraphProps) {
  const dpr = 1;
  const canvasProps = {
    width: width * dpr,
    height: height * dpr,
    scrollSpeed: width / 100 * dpr
  };

  return (
    <Box
      sx={{
        position: 'relative',
        width: '100%',
        height: '100%',
        '& > canvas': {
          position: 'absolute',
          top: 0,
          left: 0,
          right:0,
          bottom:0,
          width: '100%',
          height: '100%',
          maxWidth: '100%',
          maxHeight: '100%',
          aspectRatio: 'unset'
        }
      }}
    >
      <Channel
        idx={4}
        {...canvasProps}
        fill={paletteMantine.primaryDark[9]}
        stroke={paletteMantine.primaryLight[7]}
      />
      <Channel
        idx={6}
        {...canvasProps}
        fill={alpha(paletteMantine.secondaryDark[2], 0.3)}
        stroke={paletteMantine.secondaryLight[7]}
      />
    </Box>
  );
}
