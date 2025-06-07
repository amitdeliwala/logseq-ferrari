(ns logseq.cli
  (:require [babashka.cli :as cli]
            [logseq.graph-parser :as gp]))

(defn append! [{:keys [file bullet]}]
  (spit file (str bullet "\n") :append true))

(defn -main [& argv]
  (cli/dispatch
   {:command {:append append! :embed append!}} argv))
