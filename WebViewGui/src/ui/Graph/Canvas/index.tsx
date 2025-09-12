import { palette } from '@/define';
import Channel from './Channel';
import Box from '@mui/material/Box';
import { alpha } from '@mui/material/styles';

type EnvelopeGraphProps = {
  width?: number;
  height?: number;
};

export default function EnvelopeGraph({
  width = 383 * 2,
  height = 293 * 2,
}: EnvelopeGraphProps) {
  const canvasProps = {
    width,
    height,
    scrollSpeed: 2
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
          widnt: '100%',
          height: '100%'
        }
      }}
    >
      <Channel
        idx={4}
        {...canvasProps}
        fill={alpha(palette.primary.darkest, 1.0)}
        stroke={palette.primary.light}
      />
      <Channel
        idx={6}
        {...canvasProps}
        fill={alpha(palette.secondary.dark, 0.3)}
        stroke={palette.secondary.light}
      />
    </Box>
  );
}
