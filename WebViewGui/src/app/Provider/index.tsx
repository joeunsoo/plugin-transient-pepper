import MuiProvider from './MuiProvider';
import AboutProvider from './AboutProvider';
import AnalysisDataProvider from './AnalysisDataProvider';
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
      <AnalysisDataProvider />
      <SnackbarProvider />
    </MuiProvider>
  );
}
