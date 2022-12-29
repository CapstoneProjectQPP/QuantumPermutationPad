pipeline {
  agent any
  stages {
    stage('Build') {
      agent any
      steps {
        dir('C++') {
          sh 'make'
          archiveArtifacts artifacts: 'bin/*' , fingerprint: true
        }
      }
    }
  }
  post {

        success {
            setBuildStatus("Build succeeded", "SUCCESS");
        }
        failure {
            setBuildStatus("Build failed", "FAILURE");
        }
      // Clean after build
      always {



          cleanWs(cleanWhenNotBuilt: false,
                  deleteDirs: true,
                  disableDeferredWipeout: true,
                  notFailBuild: true,
                  patterns: [[pattern: '.gitignore', type: 'INCLUDE'],
                             [pattern: '.propsfile', type: 'EXCLUDE']])
      }
  }
}