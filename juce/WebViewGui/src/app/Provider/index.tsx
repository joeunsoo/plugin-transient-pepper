import MuiProvider from './MuiProvider';
import AboutProvider from './AboutProvider';
import SnackbarProvider from './SnackbarProvider';

type ProviderProps = {
  children: React.ReactNode
}

export default function Provider({
  children
}: ProviderProps) {
  return (
    <MuiProvider>
      {children}
      <AboutProvider />
      <SnackbarProvider />
    </MuiProvider>
  );
}
