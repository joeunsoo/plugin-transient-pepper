import Paper, { type PaperProps } from '@mui/material/Paper';

export default function StyledMainPaper({
  children, sx, ...props
}: PaperProps) {
  return (
    <Paper
      sx={{
        backgroundImage: `url('data:image/svg+xml;utf8,${encodeURIComponent(`
        <svg xmlns="http://www.w3.org/2000/svg" width="800" height="600">
          <defs>
          <filter id="filter" filterUnits="userSpaceOnUse">
            <feTurbulence type="fractalNoise" baseFrequency="0.05 0.05" numOctaves="3" result="noise" seed="2" />
            <feDiffuseLighting diffuseConstant="1" lighting-color="#999999" surfaceScale="5">
              <feDistantLight azimuth="43" elevation="60" />
            </feDiffuseLighting>

            <feColorMatrix type="matrix" values="
              0.1 0 0 0 0
              0 0.1 0 0 0
              0 0 0.1 0 0
              0 0 0 0.2 0
            "/>
          </filter>
          </defs>
          <rect width="100%" height="100%" filter="url(#filter)" />
        </svg>
      `)}')`,
        backgroundSize: 'cover',
        ...sx,
      }}
      {...props}
    >
      {children}
    </Paper>
  );
}
