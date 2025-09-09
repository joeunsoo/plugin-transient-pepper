import Paper, { type PaperProps } from '@mui/material/Paper';

export default function StyledMainPaper({
  children, sx, ...props
}: PaperProps) {
  return (
    <Paper
      sx={{
        ...sx,
      }}
      {...props}
    >
      {children}
    </Paper>
  );
}
