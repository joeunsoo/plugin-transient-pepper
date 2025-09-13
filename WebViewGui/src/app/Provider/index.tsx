import MuiProvider from './MuiProvider';
import AboutProvider from './AboutProvider';
import AnalysisDataProvider from './AnalysisDataProvider';
import SnackbarProvider from './SnackbarProvider';
import ControlParameterProvider from './ControlParameterProvider';
import ActivateProvider from './ActivateProvider';

type ProviderProps = {
  children: React.ReactNode
}

export default function Provider({
  children
}: ProviderProps) {
  return (
    <MuiProvider>
      {children}
      <ActivateProvider />
      <AboutProvider />
      <AnalysisDataProvider />
      <SnackbarProvider />
      <ControlParameterProvider />
    </MuiProvider>
  );
}
